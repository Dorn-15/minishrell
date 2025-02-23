/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:43:27 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/23 21:23:24 by altheven         ###   ########.fr       */
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
	clear_history();
}

t_alloc	*mem_exit(int err)
{
	static t_alloc	*mem = NULL;

	if (!mem)
	{
		mem = ft_calloc(1, sizeof(t_alloc));
		getcwd(mem->oldpwd, sizeof(mem->oldpwd));
		mem->exit_status = 0;
		return (mem);
	}
	free_mem(mem);
	free(mem);
	exit(err);
}
