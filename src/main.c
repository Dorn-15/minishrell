/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:48:18 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/05 18:30:58 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_cmd(char *path, char **arg, char **env)
{
	execve(path, arg, env);
	kill_cmd(errno);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	t_alloc *mem;

	mem = kill_cmd(0);
	bash_start();
	mem->cmd = read_cmd();
	while (mem->cmd)
	{
		if (*(mem->cmd))
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				kill_cmd(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				mem->cmd_tab = ft_split(mem->cmd, ' ');
				mem->cmd_path = find_path(mem->cmd_tab[0], env);
				if (!mem->cmd_path)
					cmd_not_found(mem->cmd_tab[0]);
				exec_cmd(mem->cmd_path, mem->cmd_tab, env);
			}
		}
		waitpid(pid, NULL, 0);
		if (mem->cmd)
			free(mem->cmd);
		bash_start();
		mem->cmd = read_cmd();
	}
	kill_cmd(0);
	return (0);
}
