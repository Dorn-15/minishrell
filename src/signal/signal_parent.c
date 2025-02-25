/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:45:03 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/25 17:37:18 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*parent*/
static void	signal_handler(int signum)
{
	t_alloc	*mem;

	mem = get_mem();
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_sign)
		{
			rl_redisplay();
		}
		mem->exit_status = 130;
	}
}

void	setup_parent_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*heredoc*/
static void	signal_handler_heredoc(int signum)
{
	t_alloc	*mem;

	mem = get_mem();
	if (signum == SIGINT)
	{
		mem_exit(130);
	}
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

/*signal choix*/
void	check_minishell_signal(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (len >= 10 && !strcmp(cmd + len - 10, "/minishell"))
		setup_parent_minishell();
	else
		setup_parent_fork();
}
