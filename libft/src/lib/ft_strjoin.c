/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:57:12 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:20:34 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Allocates a new string, result of the concatenation of 's1' and 's2' */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = malloc((len1 + len2 + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, len1 + 1);
	ft_strlcat(s3, s2, len1 + len2 + 1);
	return (s3);
}
