/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:41 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 15:48:14 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*chercher tous les cas particulier de export*/
void	export_cmd(char **env, char **arg)
{
	if (!arg)
		env_cmd(env);
}
