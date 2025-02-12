/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:21:32 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/12 15:34:37 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	print_export(char **env)
{
	int	i;
	int	j;
	int	b;

	i = 0;
	while (env[i])
	{
		j = 0;
		b = 0;
		ft_putstr_fd("export ", 1);
		while (env[i][j])
		{
			ft_putchar_fd(env[i][j], 1);
			if (env[i][j] == '=')
			{
				b = 1;
				ft_putchar_fd('"', 1);
			}
			j++;
		}
		if (b == 1)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
int	sort_export(char **env)
{
	char	**tmp;
	int	i;
	int	j;

	tmp = tmp_env(env);
	if (!tmp)
		return (1);
	i = 0;
	while (tmp[i])
	{
		j = i + 1;
		while (tmp[j])
		{
			if (ft_strcmp(tmp[i], tmp[j]) > 0)
				swap_env(&tmp[i], &tmp[j]);
			j++;
		}
		i++;
	}
	print_export(tmp);
	free(tmp);
	return (0);
}
