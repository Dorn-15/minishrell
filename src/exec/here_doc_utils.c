/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:22:45 by altheven          #+#    #+#             */
/*   Updated: 2025/03/09 16:47:59 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	*get_fd_here_doc(int *fd)
{
	static int	*fd_stock;

	if (!fd_stock && fd)
		fd_stock = fd;
	if (fd_stock && !fd)
		return (fd_stock);
	if (!fd_stock && !fd)
		return (NULL);
	return (fd);
}

static char	**ft_realloc(int size, int count, char *line, char **here_doc)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(size, count);
	if (!new)
		return (ft_freetab(here_doc));
	while (here_doc[i])
	{
		new[i] = here_doc[i];
		i++;
	}
	new[i] = line;
	i++;
	new[i] = NULL;
	free (here_doc);
	here_doc = NULL;
	return (new);
}

void	read_from_pipe(int fd, t_cmd **cmd)
{
	char	*line;
	char	**here_doc;
	int		count;

	count = 0;
	here_doc = ft_calloc(sizeof(char *), count + 1);
	if (!here_doc)
		return ;
	line = ft_get_next_line(fd);
	while (line)
	{
		count ++;
		here_doc = ft_realloc(sizeof(char *), count + 1, line, here_doc);
		if (!here_doc)
			return ;
		line = ft_get_next_line(fd);
	}
	ft_get_next_line(-2);
	(*cmd)->here_doc = here_doc;
}

void	read_from_here_doc(t_alloc *mem)
{
	int	i;
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	i = 0;
	while (mem->cmd->here_doc[i])
	{
		ft_putstr_fd(mem->cmd->here_doc[i], fd[1]);
		i++;
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

t_cmd	*here_doc_pars_list(t_cmd *cmd)
{
	t_cmd	*start;
	t_alloc	*mem;

	mem = get_mem();
	mem->cmd = cmd;
	start = cmd;
	while (cmd)
	{
		if (cmd->limiter)
		{
			cmd = here_doc(cmd);
			if (!cmd)
				return (ft_lstclear_pars(&start));
		}
		cmd = cmd->next;
	}
	cmd = start;
	return (cmd);
}
