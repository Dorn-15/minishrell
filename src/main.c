/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:48:18 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/13 09:50:31 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sign;

int	try_builtins(t_alloc *mem)
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

	check_minishell_signal(mem->cmd->cmd[0]);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		g_sign = 1;
		setup_child_signals();
		close(mem->stdinstock);
		close(mem->stdoutstock);
		if (!try_builtins(mem))
			mem_exit(mem->exit_status);
		mem->cmd_path = find_path(mem->cmd->cmd[0], mem->env);
		if (!mem->cmd_path || !mem->cmd->cmd[0][0])
			cmd_not_found(mem->cmd->cmd[0]);
		execve(mem->cmd_path, mem->cmd->cmd, mem->env);
		mem_exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	setup_parent_signals();
	check_status_child(status, mem);
}

static void	exec_launch(t_alloc *mem)
{
	int		fd[2];
	t_cmd	*tmp;

	fd[0] = 0;
	fd[1] = 1;
	if (*(mem->line))
	{
		mem->cmd = launch_pars(mem);
		tmp = mem->cmd;
		if (mem->cmd && !mem->cmd->next)
		{
			if (mem->cmd)
			{
				if (change_fd(mem, fd) && mem->cmd->cmd && try_builtins(mem))
					child_process(mem);
			}
		}
		else if (mem->cmd)
			multiple_pipe(mem);
		mem->cmd = tmp;
	}
}

static void	shell_loop(t_alloc *mem)
{
	mem->stdinstock = dup(0);
	mem->stdoutstock = dup(1);
	while (1)
	{
		mem->line = read_cmd();
		if (!mem->line)
			break ;
		exec_launch(mem);
		null_mem(mem);
		reset_fd(mem);
	}
	close(mem->stdinstock);
	close(mem->stdoutstock);
}

int	main(int ac, char **av, char **env)
{
	t_alloc	*mem;

	(void)ac;
	(void)av;
	mem = get_mem();
	if (!mem)
		exit(1);
	mem->env = dup_env(env);
	shell_loop(mem);
	exit_cmd(NULL, mem->exit_status);
	return (0);
}
