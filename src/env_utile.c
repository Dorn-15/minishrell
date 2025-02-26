/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:38:29 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/26 15:42:19 by adoireau         ###   ########.fr       */
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
	t_alloc	*mem;

	mem = get_mem();
	mem->env_path = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:"
		"/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
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

int	new_var_env(t_alloc *mem, char *arg, int i)
{
	char	**tmp;

	tmp = ft_calloc(i + 2, sizeof(char *));
	if (!tmp)
		return (1);
	i = 0;
	while (mem->env[i])
	{
		tmp[i] = mem->env[i];
		i++;
	}
	tmp[i] = ft_strdup(arg);
	if (!tmp[i])
	{
		free(tmp);
		return (1);
	}
	tmp[i + 1] = NULL;
	free(mem->env);
	mem->env = tmp;
	return (0);
}
