/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:19:53 by altheven          #+#    #+#             */
/*   Updated: 2025/02/26 16:25:51 by altheven         ###   ########.fr       */
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
	if (mem->cmd->fd_in != 0)
	{
		if (mem->cmd->fd_in != -1)
			dup2(mem->cmd->fd_in, pip_fd[0]);
		else
			ft_putstr_fd("Minishell = Invalid infile fd\n", 2);
		close(mem->cmd->fd_in);
	}
	if (mem->cmd->fd_out != 1)
	{
		if (mem->cmd->fd_out != -1)
			dup2(mem->cmd->fd_out, pip_fd[1]);
		else
			ft_putstr_fd("Minishell = Invalid outfile fd\n", 2);
		close(mem->cmd->fd_out);
	}
	if (mem->cmd->fd_out != -1 && mem->cmd->fd_in != -1)
		return (1);
	else
	{
		mem->exit_status = 1;
		return (0);
	}
}

static void	exec_child_process(t_alloc *mem)
{
	close(mem->stdoutstock);
	close(mem->stdinstock);
	close_fd_child(mem);
	if (!try_builtins(mem))
		mem_exit(mem->exit_status);
	mem->cmd_path = find_path(mem->cmd->cmd[0], mem->env);
	if (!mem->cmd_path)
		cmd_not_found(mem->cmd->cmd[0]);
	execve(mem->cmd_path, mem->cmd->cmd, mem->env);
	mem_exit(EXIT_FAILURE);
}

int	create_process(t_alloc *mem, int fd[2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		exec_child_process(mem);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		return (pid);
	}
}

void	multiple_pipe(t_alloc *mem)
{
	int	c;
	int	pip_fd[2];
	int	*pid;
	int	i;

	i = 0;
	c = ft_lstsize_pipe(mem->cmd);
	pid = init_tab_pid(c);
	if (!pid)
		return ;
	while (mem->cmd)
	{
		if (mem->cmd->next && pipe(pip_fd) == -1)
			return ;
		if (mem->cmd->limiter)
			here_doc(mem, pip_fd[0]);
		change_fd(mem, pip_fd);
		multiple_pipe_utils(mem, pip_fd, &i, pid);
		reset_fd(mem, pip_fd);
		mem->cmd = mem->cmd->next;
	}
	if (i > 0)
		wait_process(i, c, pid, mem);
	free(pid);
}
