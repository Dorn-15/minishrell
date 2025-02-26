/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:43:27 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/26 15:48:33 by adoireau         ###   ########.fr       */
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
	clear_history();
}

void	mem_exit(int err)
{
	t_alloc	*mem;

	mem = get_mem();
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
		return (mem);
	}
	return (mem);
}
