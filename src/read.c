/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:16:49 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/04 11:20:04 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_cmd(void)
{
	char	*buffer;
	size_t	buf_size;
	ssize_t	bytes_read;

	buffer = NULL;
	bytes_read = getline(&buffer, &buf_size, stdin);
	if (bytes_read == -1){
		free(buffer);
		return (NULL);
	}
	if (buffer[bytes_read - 1] == '\n')
		buffer[bytes_read - 1] = '\0';
	return (buffer);
}
