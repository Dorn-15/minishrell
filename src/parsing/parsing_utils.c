/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:44:44 by altheven          #+#    #+#             */
/*   Updated: 2025/03/03 13:14:36 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_cmd(char *tk_str, int i, char n)
{
	int	c;

	c = 0;
	while (tk_str[i] && tk_str[i] != '1')
	{
		if (tk_str[i] == n)
			c++;
		i++;
	}
	return (c);
}

t_cmd	*ft_lstclear_pars(t_cmd **list)
{
	t_cmd	*tmp;

	if (!list)
		return (NULL);
	tmp = *list;
	while (tmp)
	{
		*list = tmp->next;
		if (tmp->cmd)
			ft_freetab(tmp->cmd);
		if (tmp->limiter)
			ft_freetab(tmp->limiter);
		if (tmp->fd_in != 0 && tmp->fd_in != -2)
			close(tmp->fd_in);
		if (tmp->fd_out != 1)
			close(tmp->fd_out);
		if (tmp)
			free(tmp);
		tmp = *list;
	}
	return (NULL);
}

t_cmd	*fd_handler(char *tk_str, char **arg, int i, t_cmd *new_cmd)
{
	if (tk_str[i] == '8')
	{
		if (new_cmd->fd_out != 1)
			close(new_cmd->fd_out);
		new_cmd->fd_out = open(arg[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (tk_str[i] == '7')
	{
		if (new_cmd->fd_in != 0)
			close(new_cmd->fd_in);
		new_cmd->fd_in = open(arg[i], O_RDONLY, 0777);
	}
	if (tk_str[i] == '9')
	{
		if (new_cmd->fd_in != 1)
			close(new_cmd->fd_out);
		new_cmd->fd_out = open(arg[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	if (tk_str[i] == '6')
	{
		if (new_cmd->fd_in != 0 && new_cmd->fd_in != -2)
			close(new_cmd->fd_in);
		new_cmd->fd_in = -2;
	}
	return (new_cmd);
}

char	**limiter_setting(char *tk_str, char **arg, int i)
{
	int		j;
	char	**limiter;

	j = 0;
	limiter = malloc (sizeof(char *) * (count_cmd(tk_str, i, '6') + 1));
	if (!limiter)
		return (NULL);
	while (tk_str[i] && tk_str[i] != '1')
	{
		if (tk_str[i] == '6')
		{
			limiter[j] = ft_strdup(arg[i]);
			if (!limiter[j])
				return (ft_freetab(limiter), NULL);
			j++;
		}
		i++;
	}
	limiter[j] = NULL;
	return (limiter);
}
