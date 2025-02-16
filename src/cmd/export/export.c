/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:41 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/16 18:24:35 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	export_cmd(t_alloc *mem, char **arg)
{
	if (!arg || !arg[0])
		return (0);
	else if (!arg[1])
		return (sort_export(mem->env));
	else
		return (add_export(mem, arg));
}
