/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:23:11 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/16 18:57:12 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	check_export(char *arg)
{
	if (!arg || !arg[0] || arg[0] == '=' || ft_isdigit(arg[0]) || arg[0] == '-')
	{
		printf("bash: export: « %s » : not a valid identifier\n", arg);
		return (1);
	}
	return (0);
}

static int	new_export(t_alloc *mem, char *arg, int i)
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

static int	add_export_with_equal(t_alloc *mem, char *arg)
{
	int		i;
	int		len;

	while (arg[len] && arg[len] != '=')
		len++;
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
	return (new_export(mem, arg, i));
}

static int	add_export_no_equal(t_alloc *mem, char *arg)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(arg);
	while (mem->env[i])
	{
		if (!ft_strncmp(mem->env[i], arg, len)
			&& (!mem->env[i][len] || mem->env[i][len] == '='))
			return (0);
		i++;
	}
	return (new_export(mem, arg, i));
}

int	add_export(t_alloc *mem, char **arg)
{
	int		i;
	int		err;

	i = 1;
	err = 0;
	while (arg[i])
	{
		if (check_export(arg[i]))
			err = 1;
		else if (ft_strchr(arg[i], '='))
		{
			if (add_export_with_equal(mem, arg[i]))
				err = 1;
		}
		else if (add_export_no_equal(mem, arg[i]))
			err = 1;
		i++;
	}
	return (err);
}
