/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:48:18 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/10 17:56:09 by adoireau         ###   ########.fr       */
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
			cmd_not_found(mem->cmd_tab[0]);
		execve(mem->cmd_path, mem->cmd_tab, mem->env);
		mem_exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}
/*voir pour refactoriser en normalisant les in des cmd*/
static int	try_builtins(t_alloc *mem)
{
	if (!ft_strcmp(mem->cmd_tab[0], "pwd"))
	{
		pwd_cmd();
		return (0);
	}
	else if (!ft_strcmp(mem->cmd_tab[0], "exit"))
		exit_cmd(mem->cmd_tab[1]);
	else if(!ft_strcmp(mem->cmd_tab[0], "env"))
	{
		env_cmd(mem->env);
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
	mem_exit(0);
	return (0);
}
