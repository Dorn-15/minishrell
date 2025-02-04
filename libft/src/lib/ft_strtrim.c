/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:09:11 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:20:59 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Trims characters from 'set' at the beginning and end of 's1' */
size_t	ft_start_trim(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	return (i);
}

size_t	ft_end_trim(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i > 0 && ft_strchr(set, s1[i - 1]) != NULL)
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = ft_start_trim(s1, set);
	end = ft_end_trim(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	len = end - start;
	trimmed = malloc((len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, len + 1);
	return (trimmed);
}
