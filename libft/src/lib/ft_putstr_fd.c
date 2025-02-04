/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:11:34 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/24 15:20:20 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Outputs the string s to the file descriptor fd */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd != -1)
		write(fd, s, ft_strlen(s));
}
