/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_with_equal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:23:11 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/09 15:16:28 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	add_export_plus(t_alloc *mem, char *arg, int len)
{
	int		i;
	char	*tmp;

	i = len - 1;
	while (arg[++i])
		arg[i] = arg[i + 1];
	arg[i] = '\0';
	i = 0;
	while (mem->env[i])
	{
		if (!ft_strncmp(mem->env[i], arg, len)
			&& (!mem->env[i][len] || mem->env[i][len] == '='))
		{
			if (mem->env[i][len] == '=')
				len++;
			tmp = ft_strjoin(mem->env[i], arg + len);
			free(mem->env[i]);
			mem->env[i] = tmp;
			if (!mem->env[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (new_var_env(mem, arg, i));
}

static int	add_export_just_equal(t_alloc *mem, char *arg, int len)
{
	int		i;

	i = 0;
	while (mem->env[i])
	{
		if (!ft_strncmp(mem->env[i], arg, len)
			&& (!mem->env[i][len] || mem->env[i][len] == '='))
		{
			free(mem->env[i]);
			mem->env[i] = ft_strdup(arg);
			if (!mem->env[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (new_var_env(mem, arg, i));
}

int	add_export_with_equal(t_alloc *mem, char *arg)
{
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=' && arg[len] != '+')
		len++;
	if (arg[len] == '+')
		return (add_export_plus(mem, arg, len));
	else
		return (add_export_just_equal(mem, arg, len));
}
