/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:43:20 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 17:19:36 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	env_err(char **arg)
{
	if (arg[1][0] == '-') 
	{
		if (arg[1][1] == '\0' || arg[1][1] != '-')
			put_invalid_option("env", arg[1][1]);
		else
			put_unrecognized_option("env", arg[1]);
		return (125);
	}
	if (access(arg[1], F_OK) == -1) 
	{ 
		put_no_such_file("env", arg[1]); 
		return (127); 
	}
	put_permission_denied("env", arg[1]);
	return (126);
}

int	env_cmd(char **env, char **arg) {
	int	i = 0;
	
	if (!env)
		return (1);
	if (arg && arg[0] && arg[1]) 
		return (env_err(arg));
	while (env[i]) 
	{ 
		if (ft_strchr(env[i], '=')) 
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	return (0);
}
