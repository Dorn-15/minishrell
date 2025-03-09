/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:44:44 by altheven          #+#    #+#             */
/*   Updated: 2025/03/09 16:17:49 by altheven         ###   ########.fr       */
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
		if (tmp->here_doc)
			ft_freetab(tmp->here_doc);
		if (tmp->name_in)
			free(tmp->name_in);
		if (tmp->name_out)
			free(tmp->name_out);
		if (tmp)
			free(tmp);
		tmp = *list;
	}
	return (NULL);
}

static t_cmd	*out_fd_handler(char *tk_str, char **arg, int i, t_cmd *new_cmd)
{
	if (tk_str[i] == '8')
	{
		if (new_cmd->name_out != NULL)
			free(new_cmd->name_out);
		new_cmd->name_out = ft_strdup(arg[i]);
		new_cmd->append = 0;
	}
	else if (tk_str[i] == '9')
	{
		if (new_cmd->name_out != NULL)
			free(new_cmd->name_out);
		new_cmd->name_out = ft_strdup(arg[i]);
		new_cmd->append = 1;
	}
	return (new_cmd);
}

t_cmd	*fd_handler(char *tk_str, char **arg, int i, t_cmd *new_cmd)
{
	new_cmd = out_fd_handler(tk_str, arg, i, new_cmd);
	if (tk_str[i] == '7')
	{
		if (new_cmd->name_in != NULL)
			free(new_cmd->name_in);
		new_cmd->name_in = ft_strdup(arg[i]);
	}
	else if (tk_str[i] == '6')
	{
		if (new_cmd->name_in)
			free(new_cmd->name_in);
		new_cmd->name_in = NULL;
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
