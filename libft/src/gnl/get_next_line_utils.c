/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:16:08 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/30 18:55:46 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoin_gnl(char *buffer, char *temp)
{
	char	*result;
	int		i;
	int		j;

	if (!buffer || !temp)
		return (NULL);
	result = ft_calloc(ft_strlen(buffer) + ft_strlen(temp) + 1, sizeof(char));
	if (!result)
	{
		free(buffer);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (buffer[++i])
		result[i] = buffer[i];
	while (temp[j])
		result[i++] = temp[j++];
	free(buffer);
	return (result);
}

int	ft_chr_n(char *str)
{
	while (*str != '\n' && *str != 0)
		str++;
	if (*str == '\n')
		return (1);
	else
		return (0);
}

size_t	ft_size_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}
