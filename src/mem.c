/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:43:27 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/17 15:48:52 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	null_mem(t_alloc *mem)
{
	if (mem->cmd_path)
		free(mem->cmd_path);
	if (mem->cmd_tab)
		free_split(mem->cmd_tab);
	if (mem->cmd)
		free(mem->cmd);
	mem->cmd_path = NULL;
	mem->cmd_tab = NULL;
	mem->cmd = NULL;
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
		getcwd(mem->oldpwd, sizeof(mem->oldpwd));
		mem->exit_status = 0;
		return (mem);
	}
	free_mem(mem);
	free(mem);
	exit(err);
}
