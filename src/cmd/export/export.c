/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:41 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/12 15:21:55 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*chercher tous les cas particulier de export*/
int	export_cmd(char **env, char **arg)
{
	if (!arg || !arg[0])
		return (0);
	else if (!arg[1])
		return (sort_export(env));
	else
		return (1);
}
