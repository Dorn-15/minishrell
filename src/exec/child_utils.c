/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:44:53 by altheven          #+#    #+#             */
/*   Updated: 2025/03/13 09:00:26 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_fd_child(t_alloc *mem, int pip_fd[2])
{
	char_to_fd(mem);
	if (mem->cmd->fd_in != 0 && mem->cmd->fd_in != -2)
	{
		if (mem->cmd->fd_in != -1)
		{
			dup2(mem->cmd->fd_in, 0);
		}
	}
	if (mem->cmd->fd_out != 1)
	{
		if (mem->cmd->fd_out != -1)
		{
			dup2(mem->cmd->fd_out, 1);
		}
	}
	else if (mem->cmd->next)
		dup2(pip_fd[1], 1);
	close_fd_handle(mem);
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
			ft_putstr_fd("Minishell : Invalid infile fd\n", 2);
	}
	if (mem->cmd->fd_out != 1)
	{
		if (mem->cmd->fd_out != -1)
			close(mem->cmd->fd_out);
		else
			ft_putstr_fd("Minishell : Invalid outfile fd\n", 2);
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

static int	fd_open_handle(char **tab, int append)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	while (tab && tab[i])
	{
		if (fd > 1)
			close (fd);
		if (append == 0)
			fd = open(tab[i], O_WRONLY | O_CREAT
					| O_TRUNC, 0777);
		else
			fd = open(tab[i], O_WRONLY | O_CREAT
					| O_APPEND, 0777);
		i++;
	}
	return (fd);
}

void	char_to_fd(t_alloc *mem)
{
	if (mem->cmd->name_in)
		mem->cmd->fd_in = open(mem->cmd->name_in, O_RDONLY, 0777);
	else if (mem->cmd->here_doc && mem->cmd->fd_in == -2)
		read_from_here_doc(mem);
	if (mem->cmd->name_out && mem->cmd->append == 0)
	{
		if (mem->cmd->name_append)
			mem->cmd->fd_out = fd_open_handle(mem->cmd->name_append, 1);
		if (mem->cmd->fd_out > 1)
			close (mem->cmd->fd_out);
		mem->cmd->fd_out = fd_open_handle(mem->cmd->name_out, 0);
	}
	else if (mem->cmd->name_append && mem->cmd->append == 1)
	{
		if (mem->cmd->name_out)
			mem->cmd->fd_out = fd_open_handle(mem->cmd->name_out, 0);
		if (mem->cmd->fd_out > 1)
			close (mem->cmd->fd_out);
		mem->cmd->fd_out = fd_open_handle(mem->cmd->name_append, 1);
	}
}
