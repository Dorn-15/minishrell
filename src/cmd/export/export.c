/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:41 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/13 10:47:42 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	export_cmd(t_alloc *mem, char **arg)
{
	if (!arg || !arg[0])
		return (0);
	else if (!arg[1])
		return (sort_export(mem->env));
	else if (arg[1] && arg[1][0] == '-' && arg[1][1])
	{
		ft_putstr_fd("bash: export: -", 2);
		ft_putchar_fd(arg[1][1], 2);
		ft_putstr_fd(" : invalid option\n", 2);
		return (2);
	}
	else
		return (add_export(mem, arg));
}
