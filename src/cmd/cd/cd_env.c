/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:24:45 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/07 12:02:15 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*cd_getenv(char *name, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(&env[i][len + 1]));
		i++;
	}
	return (NULL);
}

void	cd_update_oldpwd(t_alloc *mem)
{
	char	*oldpwd;
	int		i;
	int		b;

	i = 0;
	b = 0;
	oldpwd = ft_strjoin("OLDPWD=", mem->oldpwd);
	while (mem->env[i])
	{
		if (ft_strncmp(mem->env[i], "OLDPWD", 6) == 0)
		{
			free(mem->env[i]);
			mem->env[i] = oldpwd;
			b = 1;
		}
		i++;
	}
	if (b == 0)
	{
		new_var_env(mem, oldpwd, i);
		free(oldpwd);
	}
}

void	cd_update_env(t_alloc *mem)
{
	int	i;

	cd_update_oldpwd(mem);
	getcwd(mem->oldpwd, sizeof(mem->oldpwd));
	i = 0;
	while (mem->env[i])
	{
		if (ft_strncmp(mem->env[i], "PWD", 3) == 0)
		{
			free(mem->env[i]);
			mem->env[i] = ft_strjoin("PWD=", mem->oldpwd);
		}
		i++;
	}
}
