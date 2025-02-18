/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:21:32 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/17 13:42:12 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	print_export_line(char *env_line)
{
	int	j;
	int	has_equal;

	j = 0;
	has_equal = 0;
	ft_putstr_fd("export ", 1);
	while (env_line[j])
	{
		ft_putchar_fd(env_line[j], 1);
		if (env_line[j] == '=' && !has_equal)
		{
			ft_putchar_fd('"', 1);
			has_equal = 1;
		}
		j++;
	}
	if (has_equal)
		ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
}

static void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2))
			print_export_line(env[i]);
		i++;
	}
}

static void	bubble_sort(char **tmp)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	while (tmp[i])
	{
		swapped = 0;
		j = 0;
		while (tmp[j + 1])
		{
			if (ft_strcmp(tmp[j], tmp[j + 1]) > 0)
			{
				swap_env(&tmp[j], &tmp[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

int	sort_export(char **env)
{
	char	**tmp;

	if (!env || !env[0])
		return (0);
	tmp = tmp_env(env);
	if (!tmp)
		return (1);
	bubble_sort(tmp);
	print_export(tmp);
	free(tmp);
	return (0);
}
