/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:20:59 by altheven          #+#    #+#             */
/*   Updated: 2025/03/05 15:35:24 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quote_counter(const char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	i++;
	while (str[i] != c)
		i++;
	return (i);
}

static size_t	ft_countword(char const *str, size_t tk, int i)
{
	int		space;

	space = 1;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			space = 1;
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] && str[i] == str[i + 1])
				i++;
			tk++;
			space = 1;
		}
		else if (str[i] && space == 1 || (str[i] == '"' || str[i] == '\''))
		{
			if (str[i] == '"' || str[i] == '\'')
				i += quote_counter(&str[i]);
			if (space == 1)
				tk++;
			space = 0;
		}
		i++;
	}
	return (tk);
}

static size_t	ft_wordlen(const char *s)
{
	size_t	i;
	char	c;

	i = 0;
	if (s[0] == '|' || s[0] == '<' || s[0] == '>')
	{
		c = s[0];
		if (s[1] && s[1] == c)
			return (2);
		else
			return (1);
	}
	while (s[i] != '\0' && !(s[i] >= 9 && s[i] <= 13) && s[i] != ' '
		&& s[i] != '|' && s[i] != '<' && s[i] != '>')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i++];
			while (s[i] != c)
				i++;
		}
		i++;
	}
	return (i);
}

static char	*ft_word_to_dest(char const *str, t_alloc *mem)
{
	char	*word;
	size_t	lenw;
	char	*tmp;

	lenw = ft_wordlen(str);
	if (is_expand(str))
	{
		tmp = ft_substr(str, 0, lenw + 1);
		if (!tmp)
			return (NULL);
		word = expand(tmp, mem);
		free(tmp);
	}
	else
	{
		word = malloc(sizeof(char) * (lenw + 1));
		if (!word)
			return (NULL);
		ft_strlcpy(word, str, lenw + 1);
	}
	word = clear_word(word);
	return (word);
}

char	**lex_split(char *str, t_alloc *mem)
{
	size_t	countw;
	size_t	w;
	char	**dest;

	countw = 0;
	w = 0;
	countw = ft_countword(str, countw, w);
	dest = malloc(sizeof(char *) * (countw + 1));
	if (!dest)
		return (NULL);
	while (w < countw && str)
	{
		if (str[0] && !(str[0] >= 9 && str[0] <= 13) && str[0] != ' ')
		{
			dest[w] = ft_word_to_dest(str, mem);
			if (!dest[w])
				return (ft_freetab(dest));
			str = str + ft_wordlen(str);
			w++;
		}
		else
			str++;
	}
	dest[w] = NULL;
	return (dest);
}
