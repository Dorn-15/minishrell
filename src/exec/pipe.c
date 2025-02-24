/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:19:53 by altheven          #+#    #+#             */
/*   Updated: 2025/02/24 11:42:51 by altheven         ###   ########.fr       */
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

void	change_fd(t_alloc *mem, int pip_fd[2])
{
	if (mem->cmd->fd_in != 0)
	{
		dup2(mem->cmd->fd_in, pip_fd[0]);
		close(mem->cmd->fd_in);
	}
	if (mem->cmd->fd_out != 1)
	{
		dup2(mem->cmd->fd_out, pip_fd[1]);
		close(mem->cmd->fd_out);
	}
}

static void	exec_child_process(t_alloc *mem)
{
	close(mem->stdoutstock);
	close(mem->stdinstock);
	if (!try_builtins(mem))
		mem_exit(mem->exit_status);
	mem->cmd_path = find_path(mem->cmd->cmd[0], mem->env);
	if (!mem->cmd_path)
		cmd_not_found(mem->cmd->cmd[0]);
	execve(mem->cmd_path, mem->cmd->cmd, mem->env);
	mem_exit(EXIT_FAILURE);
}

static void	create_process(t_alloc *mem, int fd[2])
{
	int	pid;
	int	stat;

	pid = fork();
	if (pid == -1)
		return ;
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
		waitpid(pid, &stat, 0);
		if (WIFEXITED(stat))
			mem->exit_status = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			mem->exit_status = 128 + WTERMSIG(stat);
	}
}

void	multiple_pipe(t_alloc *mem)
{
	int	c;
	int	pip_fd[2];

	if (mem->cmd->limiter)
		here_doc(mem);
	c = ft_lstsize_pipe(mem->cmd);
	while (mem->cmd)
	{
		if (mem->cmd->next)
			pipe(pip_fd);
		change_fd(mem, pip_fd);
		if (mem->cmd->cmd)
			create_process(mem, pip_fd);
		else
		{
			close(pip_fd[0]);
			close(pip_fd[1]);
		}
		if (mem->cmd->fd_out != 1)
			dup2(mem->stdoutstock, pip_fd[1]);
		if (mem->cmd->fd_in != 0)
			dup2(mem->stdinstock, pip_fd[0]);
		mem->cmd = mem->cmd->next;
	}
}
