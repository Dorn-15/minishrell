/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:19:53 by altheven          #+#    #+#             */
/*   Updated: 2025/02/20 18:39:59 by altheven         ###   ########.fr       */
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

// static void	create_process(t_alloc mem)
// {
// 	int	pid;
// 	int	fd[2];

// 	if (pipe(fd) == -1)
// 		ft_error(3);
// 	pid = fork();
// 	if (pid == -1)
// 		ft_error(3);
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], 1);
// 		close(fd[1]);
// 		exec(cmd, pip);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], 0);
// 		close(fd[0]);
// 	}
// }

void	multiple_pipe(t_alloc *mem)
{
	int	c;
	int	fd[0];

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (mem->cmd->limiter)
		here_doc(mem);
	c = ft_lstsize_pipe(mem->cmd);
	while (mem->cmd)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		if (mem->cmd->fd_in != 0)
		{
			dup2(mem->cmd->fd_in, 0);
			close(mem->cmd->fd_in);
		}
		if (mem->cmd->fd_out != 1)
			dup2(mem->cmd->fd_out, 1);
		if (mem->cmd->cmd)
			child_process(mem);
		if (mem->cmd->fd_out != 1)
			close(mem->cmd->fd_out);
		c--;
		mem->cmd = mem->cmd->next;
	}
}