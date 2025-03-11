/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:08:08 by altheven          #+#    #+#             */
/*   Updated: 2025/03/11 17:45:38 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;
	size_t	in_word;
	size_t	in_coat;

	i = 0;
	words = 0;
	in_word = 0;
	in_coat = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0 && in_coat == 0)
		{
			in_word = 1;
			words++;
		}
		else if (s[i] == c && in_word == 1 && in_coat == 0)
			in_word = 0;
		if (s[i] == '"')
			in_coat = (in_coat + 1) % 2;
		i++;
	}
	return (words);
}

static char	*allocate_word(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = ft_calloc((end - start + 1), sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	allocate_tab(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	index;
	size_t	in_coat;

	i = 0;
	index = 0;
	in_coat = 0;
	while (s[i])
	{
		if (s[i] != c && in_coat == 0)
		{
			if (s[i] == '"')
			{
				in_coat = (in_coat + 1) % 2;
				i++;
			}
			j = i;
			while (s[i] && (s[i] != c || in_coat == 1))
				if (s[i++] == '"')
					in_coat = (in_coat + 1) % 2;
			tab[index] = allocate_word(s, j, i);
			if (tab[index] == NULL)
				return (0);
			if (!s[i])
				break ;
			index++;
		}
		if (s[i] == '"')
			in_coat = (in_coat + 1) % 2;
		i++;
	}
	return (1);
}

char	**ft_split_expand(char const *s, char c)
{
	size_t	words;
	char	**tab;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = ft_calloc(words + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[words] = NULL;
	if (!allocate_tab(s, c, tab))
	{
		free_split(tab);
		return (NULL);
	}
	return (tab);
}
