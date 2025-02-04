/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:22:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/01/27 12:44:56 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Splits the string 's' into words separated by the delimiter 'c' */
static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;
	size_t	in_word;

	i = 0;
	words = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			words++;
		}
		else if (s[i] == c && in_word == 1)
			in_word = 0;
		i++;
	}
	return (words);
}

char	*allocate_word(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

int	allocate_tab(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] && s[i] != c)
				i++;
			tab[index] = allocate_word(s, j, i);
			if (tab[index] == NULL)
				return (0);
			if (!s[i])
				break ;
			index++;
		}
		i++;
	}
	return (1);
}

void	free_split(char **tab)
{
	size_t	index;

	index = 0;
	if (tab)
	{
		while (tab[index] != NULL)
			free(tab[index++]);
		free(tab);
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**tab;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
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
