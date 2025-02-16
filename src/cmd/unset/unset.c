/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:38:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/16 19:04:32 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	unset_invalid_option(char arg)
{
	ft_putstr_fd("bash: unset: -", 2);
	ft_putchar_fd(arg, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("unset: usage: unset [name ...]\n", 2);
	return (2);
}

static void	unset_rm_env(char **env, char *arg)
{
	int		i;
	int		len;

	while (arg[len] && arg[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], arg, len)
			&& (!env[i][len] || env[i][len] == '='))
		{
			free(env[i]);
			env[i] = env[i + 1];
			break ;
		}
		i++;
	}
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
}

int	unset_cmd(char **env, char **arg)
{
	int		i;

	i = 0;
	if (!arg || !env || !*arg)
		return (2);
	if (arg[1][0] == '-')
		return (unset_invalid_option(arg[1][1]));
	while (arg[i])
	{
		unset_rm_env(env, arg[i]);
		i++;
	}
	return (0);
}
