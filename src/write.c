/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:19:17 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/07 16:08:40 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bash_start(void)
{
	write(1, "minishell$ ", 11);
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (errno == EACCES)
	{
		ft_putstr_fd(": permission denied\n", 2);
		mem_exit(126);
	}
	ft_putstr_fd(": command not found\n", 2);
	mem_exit(127);
}
