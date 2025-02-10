/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:38:29 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/10 17:54:40 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**new_env(void)
{
	char **env;
	char cwd[PATH_MAX];

	env = ft_calloc(4, sizeof(char*));
	if (!env)
	{
		perror("new_env");
		mem_exit(errno);
	}
	env[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=");
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
	return(env);
}

char	**dup_env(char **env)
{
	int	i;
	char **envb;

	if (!env || !env[0])
		return (new_env());
	i = 0;
	while (env[i])
		i++;
	envb = ft_calloc(i + 1, sizeof(char*));
	if (!(envb))
	{
		perror("dup_env");
		mem_exit(errno);
	}
	i = -1;
	while (env[++i])
		envb[i] = ft_strdup(env[i]);
	return(envb);
}
