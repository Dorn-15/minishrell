/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utile2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:49:33 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/03 20:23:40 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	swap_env(char **env1, char **env2)
{
	char	*tmp;

	tmp = *env1;
	*env1 = *env2;
	*env2 = tmp;
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
