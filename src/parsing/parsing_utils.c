/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:44:44 by altheven          #+#    #+#             */
/*   Updated: 2025/02/19 11:54:13 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*ft_lstclear_pars(t_cmd **list)
{
	t_cmd	*tmp;

	if (!list)
		return (NULL);
	tmp = *list;
	while (tmp)
	{
		*list = tmp->next;
		ft_freetab(tmp->cmd);
		if (tmp->limiter)
			free(tmp->limiter);
		if (tmp)
			free(tmp);
		tmp = *list;
	}
	return (NULL);
}
