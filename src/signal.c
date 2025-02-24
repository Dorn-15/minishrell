/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:06 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/24 17:21:48 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


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
//trouver solition pour retirer le \n si ./minishell
static void	signal_handler_fork(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
}

static void	signal_handler_minishell(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
	}
}
static void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		exit(130);
	}
}

void setup_parent_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void setup_parent_fork(void)
{
	signal(SIGINT, signal_handler_fork);
	signal(SIGQUIT, SIG_IGN);
}

void setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void setup_heredoc_signals(void)
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void setup_parent_minishell(void)
{
	signal(SIGINT, signal_handler_minishell);
	signal(SIGQUIT, SIG_IGN);
}
