/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:58:22 by altheven          #+#    #+#             */
/*   Updated: 2025/03/13 08:54:00 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*token_verif(char *tk_str, char **split_arg)
{
	int	i;

	i = 0;
	while (tk_str[i])
	{
		if ((tk_str[i] == '2' || tk_str[i] == '3'
				|| tk_str[i] == '4' || tk_str[i] == '5'))
		{
			if (!tk_str[i + 1] || (tk_str[i + 1] && !(tk_str[i + 1] == '8'
						|| tk_str[i + 1] == '7' || tk_str[i + 1] == '9'
						|| tk_str[i + 1] == '6')))
			{
				free(tk_str);
				ft_putstr_fd("Invalid Token ", 2);
				ft_putstr_fd(split_arg[i], 2);
				ft_putstr_fd("\n", 2);
				return (NULL);
			}
		}
		i++;
	}
	return (tk_str);
}

static char	token_search(int i, char *tk_str, char *str)
{
	t_token	tk;

	if (str[0] == '|')
		tk = pipe_cpt;
	else if (str[0] == '<' && !str[1])
		tk = in_op;
	else if (str[0] == '>' && !str[1])
		tk = out_op;
	else if (str[0] == '<' && str[1])
		tk = here_doc_op;
	else if (str[0] == '>' && str[1])
		tk = append_op;
	else if (i > 0 && tk_str[i - 1] == '2')
		tk = fd_in_cpt;
	else if (i > 0 && tk_str[i - 1] == '3')
		tk = fd_out_cpt;
	else if (i > 0 && tk_str[i - 1] == '4')
		tk = limiter;
	else if (i > 0 && tk_str[i - 1] == '5')
		tk = append_out;
	else
		tk = cmd_cpt;
	return ('0' + tk);
}

static char	*token_asign(char *tk_str, char **split_arg)
{
	int	i;

	i = 0;
	while (split_arg[i])
	{
		tk_str[i] = token_search(i, tk_str, split_arg[i]);
		i++;
	}
	tk_str[i] = '\0';
	return (tk_str);
}

char	*lexer(char **split_arg)
{
	char	*tk_str;

	tk_str = malloc(sizeof(char) * (count_tab(split_arg) + 1));
	if (!tk_str)
		return (NULL);
	tk_str = token_asign(tk_str, split_arg);
	tk_str = token_verif(tk_str, split_arg);
	return (tk_str);
}
