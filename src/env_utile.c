/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:38:29 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/13 11:58:48 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	swap_env(char **env1, char **env2)
{
	char	*tmp;

	tmp = *env1;
	*env1 = *env2;
	*env2 = tmp;
}

static char	**new_env(void)
{
	char	**env;
	char	cwd[PATH_MAX];

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		mem_exit(EXIT_FAILURE);
	env[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/urs/bin/env");
	if (!env[0] || !env[1] || !env[2])
	{
		if (env[0])
			free(env[0]);
		if (env[1])
			free(env[1]);
		if (env[2])
			free(env[2]);
		free(env);
	}
	return (env);
}

char	**dup_env(char **env)
{
	int		i;
	char	**envb;

	if (!env || !env[0])
		return (new_env());
	i = 0;
	while (env[i])
		i++;
	envb = ft_calloc(i + 1, sizeof(char *));
	if (!(envb))
		mem_exit(EXIT_FAILURE);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
			envb[i] = ft_strdup(env[i]);
		else
			envb[i] = ft_strdup("_=/usr/bin/env");
	}
	return (envb);
}

char	**tmp_env(char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tmp = ft_calloc(i + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	return (tmp);
}
