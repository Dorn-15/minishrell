/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:16:49 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/05 22:17:08 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_cmd(void)
{
	char	*buffer;

	g_sign = 0;
	setup_parent_signals();
	buffer = readline("minishell$ ");
	if (buffer == NULL)
		return (NULL);
	if (*buffer)
		add_history(buffer);
	return (buffer);
}
