/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:45:53 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/05 22:47:06 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*fork*/
static void	signal_handler_fork(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
	}
	else if (signum == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
}

void	setup_parent_fork(void)
{
	signal(SIGINT, signal_handler_fork);
	signal(SIGQUIT, signal_handler_fork);
}

/*minishell*/
static void	signal_handler_minishell(int signum)
{
	if (signum == SIGINT)
		rl_on_new_line();
}

void	setup_parent_minishell(void)
{
	signal(SIGINT, signal_handler_minishell);
	signal(SIGQUIT, SIG_IGN);
}

/*child*/
void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
