/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case_pars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:03:29 by altheven          #+#    #+#             */
/*   Updated: 2025/03/11 16:38:34 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_if_repo(char *str, t_alloc *mem)
{
	struct stat	file;

	if (str && (str[0] == '.' || str[0] == '/'))
	{
		if (str[0] == '.' && !str[1])
		{
			ft_putstr_fd("Minishell = . filename argument required\n", 2);
			mem->exit_status = 1;
			return (1);
		}
		if (stat(str, &file) == 0)
		{
			if (S_ISDIR(file.st_mode))
			{
				ft_putstr_fd("Minishell :", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(" is a directory\n", 2);
				mem->exit_status = 126;
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}

t_cmd	*check_special_case(t_cmd *list, t_alloc *mem)
{
	t_cmd	*start;

	start = list;
	while (list)
	{
		if (list->cmd && (!ft_strncmp(list->cmd[0], ":", 1)
				|| !ft_strncmp(list->cmd[0], "!", 1)))
			list->cmd = ft_freetab(list->cmd);
		if (list->cmd && check_if_repo(list->cmd[0], mem))
			list->cmd = ft_freetab(list->cmd);
		list = list->next;
	}
	return (start);
}

int	ft_count_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

static char	**fusion_two_tab_char(char **dest, char **add, int *i)
{
	char	**tmp;
	int		j;
	int		n;

	j = 0;
	n = ft_count_tab(dest) + ft_count_tab(add) + 1;
	tmp = ft_calloc(sizeof(char *), n);
	n = 0;
	if (!tmp)
		return (ft_freetab(dest), ft_freetab(add));
	while (dest[j] && j < *i)
	{
		tmp[j] = clear_word(dest[j]);
		j++;
	}
	while (add && add[n])
		tmp[j++] = clear_word(add[n++]);
	n = *i + 1;
	*i = j;
	while (dest && dest[n])
		tmp[j++] = clear_word(dest[n++]);
	tmp[j] = NULL;
	free(dest);
	return (tmp);
}

char	**expand_and_clear(char **tab)
{
	int		i;
	size_t	lenw;
	char	*word;
	char	*tmp;
	char	**exp;

	i = 0;
	lenw = ft_wordlen(tab[i]);
	while (tab && tab[i])
	{
		lenw = ft_wordlen(tab[i]);
		if (is_expand(tab[i]))
		{
			tmp = ft_substr(tab[i], 0, lenw + 1);
			if (!tmp)
				return (NULL);
			word = expand(tmp, get_mem());
			exp = ft_split_expand(word, ' ');
			free(word);
			if (!exp)
				return (NULL);
			free (tab[i]);
			free(tmp);
			tab = fusion_two_tab_char(tab, exp, &i);
			free (exp);
		}
		i++;
	}
	return (tab);
}
