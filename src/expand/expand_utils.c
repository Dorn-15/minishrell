/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:15:30 by altheven          #+#    #+#             */
/*   Updated: 2025/03/12 17:25:55 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*tmp_create(const char *str, char **exp)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (exp[i])
		len += ft_strlen(exp[i++]);
	tmp = ft_calloc(sizeof(char), (len + 1));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}

char	*search_expand_utils(const char *str, int *i, t_alloc *mem)
{
	char	*exp_param;

	if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
		exp_param = ft_itoa(mem->exit_status);
	else if (str[*i] == '$' && str[*i + 1])
	{
		exp_param = expand_getenv(ft_substr(str, (*i + 1),
					expand_size(&str[*i + 1])), mem->env);
	}
	else if (str[*i] == '$' && !str[*i + 1])
	{
		*i += 1;
		return (ft_strdup("\0"));
	}
	*i = *i + expand_size(&str[*i + 1]);
	return (clear_word(exp_param));
}

char	*del_space_tmp(char **exp, char *tmp)
{
	int	i;

	i = ft_strlen(tmp);
	if (tmp && i > 0 && tmp[i - 1] && tmp[i - 1] == ' ')
		tmp[ft_strlen(tmp) - 1] = '\0';
	ft_freetab(exp);
	return (tmp);
}

void	quote_counter_expand(char c, int *sq, int *dq)
{
	if (c == '"')
	{
		if (*dq == 0)
			*dq = 1;
		else
			*dq = 0;
	}
	else
	{
		if (*sq == 0)
			*sq = 1;
		else
			*sq = 0;
	}
}

int	ft_count_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}
