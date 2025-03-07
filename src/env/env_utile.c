/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:38:29 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/07 16:25:08 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_path(char **env)
{
	int		i;
	t_alloc	*mem;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return ;
		i++;
	}
	mem = get_mem();
	mem->env_path = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:"
			"/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
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
	env[2] = ft_strdup("_=/usr/bin/env");
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
	get_path(env);
	return (env);
}

static char	*new_shlvl(char *env)
{
	char	*shlvl;
	char	*char_lvl;
	int		lvl;

	lvl = ft_atoi(env + 6);
	lvl++;
	char_lvl = ft_itoa(lvl);
	shlvl = ft_strjoin("SHLVL=", char_lvl);
	free(char_lvl);
	return (shlvl);
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
		if (ft_strncmp(env[i], "_=", 2) != 0
			&& ft_strncmp(env[i], "SHLVL=", 6) != 0)
			envb[i] = ft_strdup(env[i]);
		else if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			envb[i] = new_shlvl(env[i]);
		else
			envb[i] = ft_strdup("_=/usr/bin/env");
	}
	get_path(envb);
	return (envb);
}
