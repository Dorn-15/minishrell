/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:48:18 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/16 19:00:57 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	child_process(t_alloc *mem)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		mem_exit(EXIT_FAILURE);
	if (pid == 0)
	{
		mem->cmd_path = find_path(mem->cmd_tab[0], mem->env);
		if (!mem->cmd_path)
			cmd_not_found(mem->cmd_tab[0]);
		execve(mem->cmd_path, mem->cmd_tab, mem->env);
		mem_exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mem->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mem->exit_status = 128 + WTERMSIG(status);
}

//remplacer la foret de if par un double tableau
static int	try_builtins(t_alloc *mem)
{
	if (!ft_strcmp(mem->cmd_tab[0], "pwd"))
	{
		mem->exit_status = pwd_cmd(mem->cmd_tab);
		return (0);
	}
	else if (!ft_strcmp(mem->cmd_tab[0], "exit"))
	{
		mem->exit_status = exit_cmd(mem->cmd_tab);
		return (0);
	}
	else if (!ft_strcmp(mem->cmd_tab[0], "env"))
	{
		mem->exit_status = env_cmd(mem->env, mem->cmd_tab);
		return (0);
	}
	else if (!ft_strcmp(mem->cmd_tab[0], "export"))
	{
		mem->exit_status = export_cmd(mem, mem->cmd_tab);
		return (0);
	}
	else if (!ft_strcmp(mem->cmd_tab[0], "unset"))
	{
		mem->exit_status = unset_cmd(mem->env, mem->cmd_tab);
		return (0);
	}
	return (1);
}

static void	shell_loop(t_alloc *mem)
{
	while (1)
	{
		bash_start();
		mem->cmd = read_cmd();
		if (mem->cmd == NULL)
			break ;
		if (*(mem->cmd))
		{
			mem->cmd_tab = ft_split(mem->cmd, ' ');
			if (!ft_strcmp(mem->cmd_tab[0], "$?"))
			{
				free(mem->cmd_tab[0]);
				mem->cmd_tab[0] = ft_itoa(mem->exit_status);
			}
			if (try_builtins(mem))
				child_process(mem);
		}
		null_mem(mem);
	}
}

int	main(int ac, char **av, char **env)
{
	t_alloc	*mem;

	(void)ac;
	(void)av;
	mem = mem_exit(0);
	mem->env = dup_env(env);
	shell_loop(mem);
	printf("\n");
	exit_cmd(NULL);
	return (0);
}
