/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:22:45 by altheven          #+#    #+#             */
/*   Updated: 2025/03/05 10:34:16 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	*get_fd_here_doc(int *fd)
{
	static int	*fd_stock;

	if (!fd_stock && fd)
		fd_stock = fd;
	if (fd_stock && !fd)
		return (fd_stock);
	if (!fd_stock && !fd)
		return (NULL);
}
