/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:21:20 by altheven          #+#    #+#             */
/*   Updated: 2025/02/24 16:24:51 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	here_doc_read(int fd[2], char *limiter)
{
	char	*str;

	setup_heredoc_signals();
	close(fd[0]);
	str = ft_get_next_line(0);
	while (ft_strncmp(str, limiter, ft_strlen(limiter)))
	{
		ft_putstr_fd(str, fd[1]);
		free(str);
		str = ft_get_next_line(0);
	}
	free(str);
	ft_get_next_line(-2);
	close(fd[1]);
	exit(0);
}

static void	here_doc_handle(char *limiter, int i, int stdin, int stdout)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(stdin);
		close(stdout);
		here_doc_read(fd, limiter);
	}
	else
	{
		close(fd[1]);
		if (i == 1)
			dup2(fd[0], 0);
		wait(&pid);
		close(fd[0]);
	}
}

void	here_doc(t_alloc *mem)
{
	int	i;

	i = 0;
	g_sign = 1;
	while (mem->cmd->limiter[i])
	{
		if (!mem->cmd->limiter[i + 1])
			here_doc_handle(mem->cmd->limiter[i], 1,
				mem->stdinstock, mem->stdoutstock);
		else
			here_doc_handle(mem->cmd->limiter[i], 0,
				mem->stdinstock, mem->stdoutstock);
		i++;
	}
}
