/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:43:27 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/10 17:50:15 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	null_mem(t_alloc *mem)
{
	if (mem->cmd_path)
	{
		free(mem->cmd_path);
		mem->cmd_path = NULL;
	}
	if (mem->cmd_tab)
	{
		free_split(mem->cmd_tab);
		mem->cmd_tab = NULL;
	}
	if (mem->cmd)
	{
		free(mem->cmd);
		mem->cmd = NULL;
	}
}

void	free_mem(t_alloc *mem)
{
	if (mem->cmd_path)
		free(mem->cmd_path);
	if (mem->cmd_tab)
		free_split(mem->cmd_tab);
	if (mem->cmd)
		free(mem->cmd);
	if (mem->env)
		free_split(mem->env);
}

t_alloc	*mem_exit(int err)
{
	static t_alloc	*mem = NULL;

	if (!mem)
	{
		mem = ft_calloc(1, sizeof(t_alloc));
		return (mem);
	}
	free_mem(mem);
	free(mem);
	exit(err);
}
