/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:14:49 by altheven          #+#    #+#             */
/*   Updated: 2025/02/20 10:40:28 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_size(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
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
		if (str[i] == '$')
		{
			ft_strlcat(tmp, (const char *) exp[j],
				ft_strlen(exp[j]) + 1 + ft_strlen(tmp));
			len += ft_strlen(exp[j]);
			i++;
			i += expand_size(&str[i]);
			j++;
		}
		if (str[i] && str[i] != '$')
		{
			tmp[len++] = str[i++];
			tmp[len] = '\0';
		}
	}
	return (ft_freetab(exp), tmp);
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

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			exp[j] = search_expand_utils(str, &i, &j, mem);
			if (!exp[j])
				return (ft_freetab(exp));
			j++;
		}
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
	return (create_exp_line(str, exp, i, count));
}
