/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:21:20 by altheven          #+#    #+#             */
/*   Updated: 2025/03/03 13:41:01 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	verif_limiter(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*s1b;
	unsigned char	*s2b;

	if(!s1 || !s2)
		return (1);
	i = 0;
	s1b = (unsigned char *)s1;
	s2b = (unsigned char *)s2;
	while (s1b[i] && s2b[i])
	{
		if (s1b[i] != s2b[i])
			return (s1b[i] - s2b[i]);
		i++;
	}
	if (s1b[i] == '\n' && !s2b[i])
		return(0);
	return (s1b[i] - s2b[i]);
}

static void	here_doc_read(int fd[2], char *limiter)
{
	char	*str;

	setup_heredoc_signals();
	close(fd[0]);
	str = readline(">");
	while (verif_limiter(str, limiter))
	{
		ft_putstr_fd(str, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(str);
		str = readline(">");
	}
	free(str);
	close(fd[1]);
	exit(0);
}

static void	here_doc_handle(char *limiter, int i, t_alloc *mem)
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
		close(mem->stdinstock);
		close(mem->stdoutstock);
		here_doc_read(fd, limiter);
	}
	else
	{
		close(fd[1]);
		if (i == 1)
			dup2(fd[0], 0);
		close(fd[0]);
		wait(&pid);
	}
}

void	here_doc(t_alloc *mem, int fd_out)
{
	int	i;

	i = 0;
	g_sign = 1;
	(void) fd_out;
	while (mem->cmd->limiter[i])
	{
		if (!mem->cmd->limiter[i + 1])
			here_doc_handle(mem->cmd->limiter[i], 1, mem);
		else
			here_doc_handle(mem->cmd->limiter[i], 0,
				mem);
		i++;
	}
}
