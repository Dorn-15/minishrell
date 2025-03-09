/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:21:20 by altheven          #+#    #+#             */
/*   Updated: 2025/03/09 16:35:13 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_return_here_doc(int status)
{
	if (status == 33280)
		return (130);
	else
		return (0);
}

static int	verif_limiter(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*s1b;
	unsigned char	*s2b;

	if (!s1 || !s2)
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
		return (0);
	return (s1b[i] - s2b[i]);
}

static void	here_doc_read(int fd[2], char *limiter, t_cmd *cmd)
{
	char	*str;

	setup_heredoc_signals();
	close(fd[0]);
	get_fd_here_doc(fd);
	str = readline(">");
	while (str != NULL && verif_limiter(str, limiter))
	{
		ft_putstr_fd(str, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(str);
		str = readline(">");
	}
	if (str)
		free(str);
	else
		ft_putstr_fd("bash: warning: here-document delimited by"
			"end-of-file (wanted `limiter')\n", 2);
	close(fd[1]);
	ft_lstclear_pars(&cmd);
	mem_exit(0);
}

static int	here_doc_handle(char *limiter, int i, t_alloc *mem, t_cmd **cmd)
{
	int	pid;
	int	fd[2];
	int	status;

	status = 0;
	if (pipe(fd) == -1)
		mem_exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		mem_exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(mem->stdinstock);
		close(mem->stdoutstock);
		here_doc_read(fd, limiter, *(cmd));
	}
	else
	{
		close(fd[1]);
		if (i == 1)
			read_from_pipe(fd[0], cmd);
		waitpid(pid, &status, 0);
		close(fd[0]);
	}
	return (check_return_here_doc(status));
}

t_cmd	*here_doc(t_cmd *cmd)
{
	int		i;
	int		r;
	t_alloc	*mem;

	mem = get_mem();
	i = 0;
	r = 0;
	g_sign = 1;
	while (cmd->limiter[i] && r != 130)
	{
		if (!cmd->limiter[i + 1])
			r = here_doc_handle(cmd->limiter[i], 1, mem, &cmd);
		else
			r = here_doc_handle(cmd->limiter[i], 0, mem, &cmd);
		i++;
	}
	if (r == 130)
		return (NULL);
	mem->exit_status = 0;
	return (cmd);
}
