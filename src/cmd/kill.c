/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:14:12 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/05 18:24:12 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_mem(t_alloc **mem)
{
	(*mem)->cmd_path = NULL;
	(*mem)->cmd_tab = NULL;
	(*mem)->cmd = NULL;
}

static void	free_mem(t_alloc *mem)
{
	if (mem->cmd_path)
		free(mem->cmd_path);
	if (mem->cmd_tab)
		free_split(mem->cmd_tab);
	if (mem->cmd)
		free(mem->cmd);
	free(mem);
}

t_alloc	*kill_cmd(int err)
{
	static t_alloc	*mem = NULL;

	if (!mem)
	{
		mem = malloc(sizeof(t_alloc));
		init_mem(&mem);
		return (mem);
	}
	free_mem(mem);
	exit(err);
}
