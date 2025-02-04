/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:03:58 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:20:53 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Searches for substring srch in ref within n characters */
char	*ft_strnstr(const char *ref, const char *srch, size_t n)
{
	size_t	i;
	size_t	j;

	if (!ref && n == 0)
		return (NULL);
	if (ft_strlen(srch) == 0)
		return ((char *) ref);
	i = 0;
	while (ref[i] && i < n)
	{
		if (ref[i] == srch[0])
		{
			j = 0;
			while (ref[i + j] && srch[j]
				&& ref[i + j] == srch[j]
				&& (i + j) < n)
				j++;
			if (srch[j] == '\0')
				return ((char *)ref + i);
		}
		i++;
	}
	return (NULL);
}
