/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:14:22 by altheven          #+#    #+#             */
/*   Updated: 2025/02/19 12:56:47 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_pipe(char *str)
{
	int	i;
	int	c;

	i = 1;
	c = 0;
	while (str[i])
	{
		if (str[i] && str[i] != '|' && str[i] != ' ' && str[i] != '\t'
			&& str[i] != '\n')
			c++;
		if (str[i] == '|' && c > 0)
			return (1);
		else if (str[i] == '|' && c == 0)
			return (0);
		i++;
	}
	if (c > 0)
		return (1);
	return (0);
}

static int	check_carac(char c)
{
	if (c == '&' || c == ';' || c == '\\')
		return (0);
	return (1);
}

static int	check_quote(char *str, int *j)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i])
	{
		if (str[i] == c && i != 0)
		{
			*j += i;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*clear_param(char *str)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !check_quote(&str[i], &i))
			return (error_clear(str));
		if (!check_carac(str[i]))
			return (error_clear(str));
		if (str[i] == '|' && !check_pipe(&str[i]))
			return (error_clear(str));
		if (str[i] && str[i] != '|' && str[i] != ' ' && str[i] != '\t'
			&& str[i] != '\n')
			c++;
		if (str[i] == '|' && c == 0)
			return (error_clear(str));
		i++;
	}
	return (str);
}
