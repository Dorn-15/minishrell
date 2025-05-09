/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:50:44 by altheven          #+#    #+#             */
/*   Updated: 2025/03/11 16:27:51 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_cmd	*search_cmd(char *tk_str, char **arg, int i, t_cmd *new_cmd)
{
	int	n;
	int	c;

	n = i;
	c = count_cmd(tk_str, i, '0');
	new_cmd->cmd = ft_calloc(sizeof(char *), (c + 1));
	if (!new_cmd->cmd)
		return (NULL);
	i = n;
	n = 0;
	while (tk_str[i] && tk_str[i] != '1')
	{
		if (tk_str[i] == '0')
		{
			new_cmd->cmd[n] = ft_strdup(arg[i]);
			if (!new_cmd->cmd[n])
				return (ft_freetab(new_cmd->cmd), NULL);
			n++;
		}
		i++;
	}
	new_cmd->cmd[n] = NULL;
	new_cmd->cmd = expand_and_clear(new_cmd->cmd);
	return (new_cmd);
}

static t_cmd	*search_fd(char *tk_str, char **arg, int i, t_cmd *new_cmd)
{
	new_cmd->name_append = NULL;
	new_cmd->limiter = NULL;
	new_cmd->fd_in = 0;
	new_cmd->fd_out = 1;
	new_cmd->name_in = NULL;
	new_cmd->name_out = NULL;
	new_cmd->append = 0;
	new_cmd->here_doc = NULL;
	new_cmd->next = NULL;
	while (tk_str[i] && tk_str[i] != '1')
	{
		if (tk_str[i] == '6' && !new_cmd->limiter)
		{
			new_cmd->limiter = limiter_setting(tk_str, arg, i);
			if (!new_cmd->limiter)
			{
				free(new_cmd);
				return (NULL);
			}
		}
		new_cmd = fd_handler(tk_str, arg, i, new_cmd);
		i++;
	}
	return (new_cmd);
}

static t_cmd	*create_new_node(char *tk_str, char **split_arg, int *i)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd = search_fd(tk_str, split_arg, *i, new_cmd);
	if (!new_cmd)
		return (NULL);
	new_cmd = search_cmd(tk_str, split_arg, *i, new_cmd);
	if (!new_cmd)
		return (NULL);
	if (new_cmd->cmd && !new_cmd->cmd[0])
		new_cmd->cmd = ft_freetab(new_cmd->cmd);
	while (tk_str[*i] != '1' && tk_str[*i])
		*i += 1;
	if (tk_str[*i] == '1')
		*i += 1;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*parsing_list(char *tk_str, char **split_arg)
{
	t_cmd	*new_cmd;
	t_cmd	*list;
	int		i;
	int		n;

	n = 0;
	i = 0;
	new_cmd = create_new_node(tk_str, split_arg, &i);
	list = new_cmd;
	while (tk_str[i] && new_cmd)
	{
		n++;
		if (n > 250)
			return (ft_lstclear_pars(&list));
		new_cmd->next = create_new_node(tk_str, split_arg, &i);
		if (!new_cmd)
			return (ft_lstclear_pars(&list));
		new_cmd = new_cmd->next;
	}
	ft_freetab(split_arg);
	return (list);
}

t_cmd	*launch_pars(t_alloc *mem)
{
	char	*str;
	char	**split_arg;
	char	*tk_str;
	t_cmd	*list;

	str = clear_param(mem->line);
	if (!str)
		return (error_pars(1, NULL, NULL, mem));
	split_arg = lex_split(str);
	if (!split_arg)
		return (error_pars(0, NULL, NULL, mem));
	tk_str = lexer(split_arg);
	if (!tk_str)
		return (error_pars(0, split_arg, NULL, mem));
	list = parsing_list(tk_str, split_arg);
	if (!list)
		return (error_pars(0, NULL, tk_str, mem));
	split_arg = NULL;
	free (tk_str);
	list = here_doc_pars_list(list);
	if (!list)
		return (NULL);
	list = check_special_case(list, mem);
	return (list);
}
