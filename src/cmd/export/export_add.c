/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:23:11 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/27 11:41:14 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	check_export(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0] || arg[0] == '=' || ft_isdigit(arg[0]) || arg[0] == '-')
	{
		printf("bash: export: `%s' : not a valid identifier\n", arg);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("bash: export: `%s' : not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_export_with_equal(t_alloc *mem, char *arg)
{
	int		i;
	int		len;

	len = 0;
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
	return (new_var_env(mem, arg, i));
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
	return (new_var_env(mem, arg, i));
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
			if (ft_strncmp(arg[i], "PATH=", 5) == 0 && get_mem()->env_path)
				free(get_mem()->env_path);
			if (add_export_with_equal(mem, arg[i]))
				err = 1;
		}
		else if (add_export_no_equal(mem, arg[i]))
			err = 1;
		i++;
	}
	return (err);
}
