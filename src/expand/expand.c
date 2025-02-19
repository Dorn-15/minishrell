/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:14:49 by altheven          #+#    #+#             */
/*   Updated: 2025/02/19 12:57:03 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	expand_size(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	return (i);
}

static char	*create_exp_line(const char *str, char **exp)
{
	char	*tmp;
	int		i;
	int		len;
	int		j;

	j = 0;
	i = 0;
	len = ft_strlen(str);
	while (exp[i])
		len += ft_strlen(exp[i++]);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	i = 0;
	len = 0;
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
	return (tmp);
}

static char	*search_getenv(char *name, char **env)
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
	return (ft_strdup("\0"));
}

static char	**search_expand(const char *str, char **exp, char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, i + 1, expand_size(&str[i + 1]));
			if (!tmp)
				return (ft_freetab(exp));
			exp[j] = search_getenv(tmp, envp);
			free(tmp);
			if (!exp[j])
				return (ft_freetab(exp));
			i = i + expand_size(&str[i + 1]);
			j++;
		}
		i++;
	}
	exp[j] = NULL;
	return (exp);
}

char	*expand(const char *str, char **envp)
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
	exp = search_expand(str, exp, envp);
	if (!exp)
		return (NULL);
	ft_freetab(exp);
	return (create_exp_line(str, exp));
}
