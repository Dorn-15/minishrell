/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:44:53 by altheven          #+#    #+#             */
/*   Updated: 2025/03/05 12:29:44 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_fd_child(t_alloc *mem, int pip_fd[2])
{
	if (mem->cmd->fd_in != 0 && mem->cmd->fd_in != -2)
	{
		if (mem->cmd->fd_in != -1)
		{
			dup2(mem->cmd->fd_in, 0);
			close(mem->cmd->fd_in);
		}
	}
	if (mem->cmd->fd_out != 1)
	{
		if (mem->cmd->fd_out != -1)
		{
			dup2(mem->cmd->fd_out, 1);
			close(mem->cmd->fd_out);
		}
	}
	else if (mem->cmd->next)
		dup2(pip_fd[1], 1);
	if (mem->cmd->fd_out != -1 && mem->cmd->fd_in != -1)
		return (1);
	else
		return (0);
}

void	close_fd_handle(t_alloc *mem)
{
	if (mem->cmd->fd_in != 0 && mem->cmd->fd_in != -2)
	{
		if (mem->cmd->fd_in != -1)
			close(mem->cmd->fd_in);
		else
			ft_putstr_fd("Minishell = Invalid infile fd\n", 2);
	}
	if (mem->cmd->fd_out != 1)
	{
		if (mem->cmd->fd_out != -1)
			close(mem->cmd->fd_out);
		else
			ft_putstr_fd("Minishell = Invalid outfile fd\n", 2);
	}
	if (mem->cmd->fd_out != -1 && mem->cmd->fd_in != -1)
		return ;
	else
	{
		mem->exit_status = 1;
		return ;
	}
}

void	check_status_child(int status, t_alloc *mem)
{
	if (WIFEXITED(status))
		mem->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mem->exit_status = 128 + WTERMSIG(status);
}
