/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:19:53 by altheven          #+#    #+#             */
/*   Updated: 2025/03/13 09:52:11 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_lstsize_pipe(t_cmd*lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	change_fd(t_alloc *mem, int pip_fd[2])
{
	char_to_fd(mem);
	if (mem->cmd->fd_in != 0 && mem->cmd->fd_in != -2)
	{
		if (mem->cmd->fd_in != -1)
			dup2(mem->cmd->fd_in, pip_fd[0]);
	}
	if (mem->cmd->fd_out != 1)
	{
		if (mem->cmd->fd_out != -1)
			dup2(mem->cmd->fd_out, pip_fd[1]);
	}
	close_fd_handle(mem);
	if (mem->cmd->fd_out != -1 && mem->cmd->fd_in != -1)
		return (1);
	else
	{
		mem->exit_status = 1;
		return (0);
	}
}

static void	exec_child_process(t_alloc *mem, int pip[2])
{
	t_alloc	*tmp;

	tmp = get_mem();
	close(mem->stdoutstock);
	close(mem->stdinstock);
	change_fd_child(mem, pip);
	close(pip[1]);
	close_fd_child(mem);
	if (!try_builtins(mem))
	{
		tmp->env = mem->env;
		mem_exit(mem->exit_status);
	}
	mem->cmd_path = find_path(mem->cmd->cmd[0], mem->env);
	if (!mem->cmd_path || !mem->cmd->cmd[0][0])
		cmd_not_found(mem->cmd->cmd[0]);
	execve(mem->cmd_path, mem->cmd->cmd, mem->env);
	if (!tmp->cmd_path && mem->cmd_path)
		tmp->cmd_path = mem->cmd_path;
	mem_exit(EXIT_FAILURE);
}

int	create_process(t_alloc *mem, int fd[2])
{
	int	pid;

	check_minishell_signal(mem->cmd->cmd[0]);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		g_sign = 1;
		setup_child_signals();
		close(fd[0]);
		exec_child_process(mem, fd);
	}
	else
	{
		close(fd[1]);
		if ((mem->cmd->next && mem->cmd->next->fd_in == 0) || !mem->cmd->next)
			dup2(fd[0], 0);
		if ((mem->cmd->next && mem->cmd->next->fd_in == -2))
			waitpid(pid, NULL, 0);
		close(fd[0]);
	}
	return (pid);
}

void	multiple_pipe(t_alloc *mem)
{
	int		c;
	int		pip_fd[2];
	int		i;
	t_alloc	tmp;

	c = ft_lstsize_pipe(mem->cmd);
	mem->pid = init_tab_pid(c);
	if (!mem->pid)
		return ;
	tmp = *mem;
	i = 0;
	while (tmp.cmd)
	{
		if (pipe(pip_fd) == -1)
			return ;
		multiple_pipe_utils(&tmp, pip_fd, &i, tmp.pid);
		tmp.cmd = tmp.cmd->next;
	}
	if (i > 0)
		wait_process(i, c, tmp.pid, mem);
	setup_parent_signals();
}
