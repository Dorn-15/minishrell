/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:48:18 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/04 12:29:37 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_cmd(char *path, char **arg, char **env)
{
	execve(path, arg, env);
	free(path);
	free(arg);
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	char	*cmd_path;
	char	**cmd_tab;
	__pid_t	pid;

	bash_start();
	cmd = read_cmd();
	while (cmd) {
		if (!*cmd)
			printf("cmd = NULL\n");
		else
		{
			//a remplacer par le parsing
			pid = fork();
			if (pid == -1)
			{
				free_split(cmd_tab);
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				cmd_tab = ft_split(cmd, ' ');
				cmd_path = find_path(cmd_tab[0], env);
				if (!cmd_path)
				{
					ft_putstr_fd(cmd_tab[0], 2);
					ft_putstr_fd(": command not found\n", 2);
					free_split(cmd_tab);
					exit(127);
				}
				exec_cmd(cmd_path, cmd_tab, env);
			}
		}
		waitpid(pid, NULL, 0);
		if (cmd)
			free(cmd);
		bash_start();
		cmd = read_cmd();
	}
	printf("exit \n");
	return (0);
}
