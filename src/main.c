/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:48:18 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 17:26:13 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	child_process(t_alloc *mem)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		mem_exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		mem->cmd_path = find_path(mem->cmd_tab[0], mem->env);
		if (!mem->cmd_path)
		{
			cmd_not_found(mem->cmd_tab[0]);
			mem_exit(127);
		}
		execve(mem->cmd_path, mem->cmd_tab, mem->env);
		mem_exit(EXIT_FAILURE);
	}
	// uniquement pour le dernier enfant
	waitpid(pid, NULL, 0);
}

static int	try_builtins(t_alloc *mem)
{
	if (!ft_strcmp(mem->cmd_tab[0], "pwd"))
	{
		mem->exit_status = pwd_cmd(mem->env, mem->cmd_tab[1]);
		return (0);
	}
	else if (!ft_strcmp(mem->cmd_tab[0], "exit"))
	{
		mem->exit_status = exit_cmd(mem->cmd_tab);
		return (0);
	}
	else if(!ft_strcmp(mem->cmd_tab[0], "env"))
	{
		mem->exit_status = env_cmd(mem->env, mem->cmd_tab);
		return (0);
	}
	else if (!ft_strcmp(mem->cmd_tab[0], "$?"))
	{
		ft_putstr_fd("bash: ", 1);
		ft_putnbr_fd(mem->exit_status, 1);
		ft_putstr_fd(": command not found\n", 1);
		return (0);
	}
	return (1);
}

static void	shell_loop(t_alloc *mem)
{
	int	cmd_val;

	while (1)
	{
		bash_start();
		mem->cmd = read_cmd();
		if (!mem->cmd)
			break ;
		if (*(mem->cmd))
		{
			//parsing
			mem->cmd_tab = ft_split(mem->cmd, ' ');
			/*si pas de pipe et bultins
			exec a l'exterieur de chil*/
			if (try_builtins(mem))
			{
			/*while (tant que pip)
			{*/
				child_process(mem);
			//}
			}
		}
		null_mem(mem);
	}
}

int	main(int ac, char **av, char **env)
{
	t_alloc	*mem;

	mem = mem_exit(0);
	mem->env = dup_env(env);
	shell_loop(mem);
	printf("\n");
	exit_cmd(NULL);
	return (0);
}
