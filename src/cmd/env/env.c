/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:43:20 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/16 18:19:42 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	env_err(char **arg)
{
	struct stat	st;

	if (arg[1][0] == '-')
	{
		if (arg[1][1] == '\0' || arg[1][1] != '-')
			env_invalid_option(arg[1][1]);
		else
			env_unrecognized_option(arg[1]);
		return (125);
	}
	{
		if (stat(arg[1], &st) == -1)
		{
			env_no_such_file(arg[1]);
			return (127);
		}
		if (S_ISDIR(st.st_mode))
		{
			env_permission_denied(arg[1]);
			return (126);
		}
		env_no_such_file(arg[1]);
		return (127);
	}
}

int	env_cmd(char **env, char **arg)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	if (arg && arg[0] && arg[1])
		return (env_err(arg));
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
