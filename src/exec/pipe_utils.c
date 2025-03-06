/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:11:54 by altheven          #+#    #+#             */
/*   Updated: 2025/03/06 14:43:54 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_fd(t_alloc *mem, int pip_fd[2])
{
	int	fd_in;
	int	fd_out;

	if (mem->cmd->fd_out != 1)
	{
		fd_out = dup(mem->stdoutstock);
		dup2(fd_out, pip_fd[1]);
		close(fd_out);
	}
	if (mem->cmd->fd_in != 0)
	{
		fd_in = dup(mem->stdinstock);
		dup2(fd_in, pip_fd[0]);
		close(fd_in);
	}
}

int	*init_tab_pid(int c)
{
	int	*tab;

	tab = ft_calloc(sizeof(int), c);
	if (!tab)
		return (NULL);
	else
		return (tab);
}

void	wait_process(int i, int c, int *pid, t_alloc *mem)
{
	int	stat;

	i = 0;
	while (i < c)
	{
		stat = 0;
		if (pid[i] != 0)
		{
			waitpid(pid[i], &stat, 0);
			if (WIFEXITED(stat))
				mem->exit_status = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				mem->exit_status = 128 + WTERMSIG(stat);
		}
		i++;
	}
}

void	multiple_pipe_utils(t_alloc *mem, int pip_fd[2], int *i, int *pid)
{
	if (mem->cmd->cmd && mem->cmd->fd_out != -1
		&& mem->cmd->fd_in != -1)
	{
		pid[*i] = create_process(mem, pip_fd);
		*i += 1;
	}
	else
	{
		close(pip_fd[0]);
		close(pip_fd[1]);
	}
	close_fd_handle(mem);
}

void	close_fd_child(t_alloc *mem)
{
	t_cmd	*cmd;

	cmd = mem->cmd;
	cmd = cmd->next;
	while (cmd)
	{
		if (cmd->fd_in != 0 && cmd->fd_in != -2)
			close (cmd->fd_in);
		if (cmd->fd_out != 1)
			close (cmd->fd_out);
		cmd = cmd->next;
	}
}
