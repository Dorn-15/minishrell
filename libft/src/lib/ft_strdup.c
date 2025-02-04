/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:44:18 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:20:30 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* allocate memory and duplicate the string. */
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s) + 1;
	s2 = malloc(len * sizeof(char));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s, len);
	return (s2);
}
