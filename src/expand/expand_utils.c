/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:15:30 by altheven          #+#    #+#             */
/*   Updated: 2025/03/04 11:51:06 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*tmp_create(const char *str, char **exp)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (exp[i])
		len += ft_strlen(exp[i++]);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}

char	*search_expand_utils(const char *str, int *i, int *j, t_alloc *mem)
{
	char	*exp_param;

	if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
		exp_param = ft_itoa(mem->exit_status);
	else
	{
		exp_param = expand_getenv(ft_substr(str, (*i + 1),
					expand_size(&str[*i + 1])), mem->env);
	}
	*i = *i + expand_size(&str[*i + 1]);
	return (exp_param);
}
