/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:48:18 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/21 12:11:59 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	try_builtins(t_alloc *mem)
{
	static char	*builtins[7] = {"pwd", "exit", "env",
		"export", "unset", "cd", "echo"};
	int			i;

	i = 0;
	while (i < 7 && ft_strcmp(mem->cmd->cmd[0], builtins[i]))
		i++;
	if (i >= 7)
		return (1);
	else if (i == 0)
		mem->exit_status = pwd_cmd(mem->cmd->cmd);
	else if (i == 1)
		mem->exit_status = exit_cmd(mem->cmd->cmd, mem->exit_status);
	else if (i == 2)
		mem->exit_status = env_cmd(mem->env, mem->cmd->cmd);
	else if (i == 3)
		mem->exit_status = export_cmd(mem, mem->cmd->cmd);
	else if (i == 4)
		mem->exit_status = unset_cmd(mem->env, mem->cmd->cmd);
	else if (i == 5)
		mem->exit_status = cd_cmd(mem, mem->cmd->cmd);
	else if (i == 6)
		mem->exit_status = echo_cmd(mem->cmd->cmd);
	return (0);
}

void	child_process(t_alloc *mem)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		mem_exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (!try_builtins(mem))
			mem_exit(mem->exit_status);
		mem->cmd_path = find_path(mem->cmd->cmd[0], mem->env);
		if (!mem->cmd_path)
			cmd_not_found(mem->cmd->cmd[0]);
		execve(mem->cmd_path, mem->cmd->cmd, mem->env);
		mem_exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mem->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mem->exit_status = 128 + WTERMSIG(status);
}

static void	shell_loop(t_alloc *mem)
{
	t_cmd	*tmp;
	int		stdinstock;

	stdinstock = dup(0);
	while (1)
	{
		dup2(stdinstock, 0);
		mem->line = read_cmd();
		if (mem->line == NULL)
			break ;
		if (*(mem->line))
		{
			mem->cmd = launch_pars(mem);
			if (mem->cmd && !mem->cmd->next)
			{
				if (mem->cmd->limiter)
					here_doc(mem);
				if (try_builtins(mem))
					child_process(mem);
			}
			else if (mem->cmd)
			{
				tmp = mem->cmd;
				//ajouter les pipe
				while (tmp->next)
				{
					child_process(mem);
					tmp = tmp->next;
				}
				child_process(mem);
			}
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
	exit_cmd(NULL, mem->exit_status);
	return (0);
}
