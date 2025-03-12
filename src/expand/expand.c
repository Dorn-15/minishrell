/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:14:49 by altheven          #+#    #+#             */
/*   Updated: 2025/03/12 17:19:18 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_size(const char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if ((str[i] == '$' && !str[i + 1]) || ((str[i] == '$' && str[i + 1])
			&& ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')))
		return (i);
	else if (str[i] == '$')
		i++;
	if (str[i] && !(ft_isalpha(str[i]) || str[i] == '_'
			|| str[i] == '?'))
		return (i + 1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
	{
		if (str[i] == '?')
			return (i + 1);
		i++;
	}
	return (i);
}

static char	*create_exp_line(const char *str, char **exp, int i, int j)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = tmp_create(str, exp);
	if (!tmp)
		return (ft_freetab(exp), NULL);
	while (str[i])
	{
		if (str[i] == '$' && exp[j])
		{
			ft_strlcat(tmp, (const char *) exp[j],
				ft_strlen(exp[j]) + 1 + ft_strlen(tmp));
			len += ft_strlen(exp[j]);
			i += expand_size(&str[i]);
			j++;
		}
		else if (str[i])
		{
			tmp[len++] = str[i++];
			tmp[len] = '\0';
		}
	}
	return (del_space_tmp(exp, tmp));
}

char	*expand_getenv(char *name, char **env)
{
	int	i;
	int	len;

	i = 0;
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (free(name), ft_strdup(&env[i][len + 1]));
		i++;
	}
	return (free(name), ft_strdup("\0"));
}

static char	**search_expand(const char *str, char **exp, t_alloc *mem)
{
	int		i;
	int		j;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			quote_counter_expand(str[i], &sq, &dq);
		if ((str[i] == '$' && dq == 1) || (str[i] == '$' && sq == 0))
		{
			exp[j] = search_expand_utils(str, &i, mem);
			if (!exp[j])
				return (ft_freetab(exp));
			j++;
		}
		else
			i++;
	}
	exp[j] = NULL;
	return (exp);
}

char	*expand(const char *str, t_alloc *mem)
{
	int		i;
	int		count;
	char	**exp;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	exp = malloc(sizeof(char *) * (count + 1));
	if (!exp)
		return (NULL);
	exp = search_expand(str, exp, mem);
	if (!exp)
		return (NULL);
	i = 0;
	count = 0;
	return (create_exp_line(str, exp, count, i));
}
