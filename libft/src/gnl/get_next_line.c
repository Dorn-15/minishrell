/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:18:17 by adoireau          #+#    #+#             */
/*   Updated: 2024/11/30 18:49:07 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	ft_free_buffer(char **buffer)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		if (buffer[i])
		{
			free(buffer[i]);
			buffer[i] = NULL;
		}
		i++;
	}
}

char	*extract_line(char *buffer, size_t size_line)
{
	char	*line;
	size_t	j;

	if (!buffer[0])
		return (NULL);
	line = ft_calloc(size_line + 1, sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < size_line)
	{
		line[j] = buffer[j];
		j++;
	}
	return (line);
}

char	*update_buffer(char *buffer, size_t size_line)
{
	char	*new_buffer;
	size_t	j;

	if (!buffer[size_line])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_calloc(ft_strlen(buffer) - size_line + 1, sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[size_line])
		new_buffer[j++] = buffer[size_line++];
	free(buffer);
	return (new_buffer);
}

static char	*r_buffer(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_chr_n(temp))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, temp);
		if (!buffer)
			break ;
	}
	free(temp);
	return (buffer);
}

char	*ft_get_next_line(int fd)
{
	static char	*buffer[1024] = {NULL};
	char		*line;
	size_t		size_line;

	if (fd == -2)
	{
		ft_free_buffer(buffer);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(1, sizeof(char));
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = r_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	size_line = ft_size_line(buffer[fd]);
	line = extract_line(buffer[fd], size_line);
	buffer[fd] = update_buffer(buffer[fd], size_line);
	return (line);
}
