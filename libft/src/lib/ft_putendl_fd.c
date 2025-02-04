/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:17:39 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:20:13 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Outputs the string s followed by a newline to the file descriptor fd */
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd != -1)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
}
