/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:43:27 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/05 11:49:22 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	null_mem(t_alloc *mem)
{
	if (mem->cmd_path)
		free(mem->cmd_path);
	if (mem->line)
		free(mem->line);
	if (mem->cmd)
		ft_lstclear_pars(&mem->cmd);
	mem->cmd_path = NULL;
	mem->line = NULL;
	mem->cmd = NULL;
}

void	free_mem(t_alloc *mem)
{
	if (mem->cmd_path)
		free(mem->cmd_path);
	if (mem->line)
		free(mem->line);
	if (mem->env)
		free_split(mem->env);
	if (mem->cmd)
		ft_lstclear_pars(&mem->cmd);
	if (mem->env_path)
		free(mem->env_path);
	if (mem->pid)
		free(mem->pid);
	clear_history();
}

void	mem_exit(int err)
{
	t_alloc	*mem;
	int		*fd;

	mem = get_mem();
	fd = get_fd_here_doc(NULL);
	if (fd)
		close(fd[1]);
	close(mem->stdoutstock);
	close(mem->stdinstock);
	free_mem(mem);
	free(mem);
	exit(err);
}

t_alloc	*get_mem(void)
{
	static t_alloc	*mem = NULL;

	if (!mem)
	{
		mem = ft_calloc(1, sizeof(t_alloc));
		getcwd(mem->oldpwd, sizeof(mem->oldpwd));
		mem->exit_status = 0;
		mem->env_path = NULL;
		mem->pid = NULL;
		return (mem);
	}
	return (mem);
}
