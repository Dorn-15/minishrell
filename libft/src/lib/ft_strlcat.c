/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:41:56 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:20:37 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Appends src to dst of size dsize; returns total length */
size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (dsize <= len_dst)
		return (dsize + len_src);
	i = len_dst;
	j = 0;
	while (src[j] && (i + 1 < dsize))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (len_dst + len_src);
}
