/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:31:11 by altheven          #+#    #+#             */
/*   Updated: 2025/02/19 11:54:16 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_freetab(char **dest)
{
	size_t	w;

	w = 0;
	while (dest[w])
	{
		free(dest[w]);
		w++;
	}
	free(dest);
	return (NULL);
}

int	count_tab(char**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_expand(const char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] != '\0' && !(str[i] >= 9 && str[i] <= 13) && str[i] != ' '
		&& str[i] != '|' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '$')
			return (1);
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] != c)
			{
				if (str[i] == '$' && c == '"')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

char	*clear_word(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[j])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			j = i + 1;
			c = str[i];
			while (str[j] && str[j] != c)
				str[i++] = str[j++];
			j++;
		}
		else
			str[i++] = str[j++];
	}
	str[i] = '\0';
	return (str);
}
