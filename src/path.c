/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:32 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/13 09:55:36 by altheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* try to access at cmd if start by '.' or '/' */
static char	*try_direct_path(char *cmd)
{
	if (!cmd)
		return (NULL);
	if ((cmd[0] == '/' || cmd[0] == '.') && access(cmd, X_OK) == 0)
		return (cmd);
	if (errno == EACCES)
		cmd_not_found(cmd);
	return (NULL);
}

/* join potential path to cmd name & try to access */
static char	*try_path(char *path_dir, char *cmd)
{
	char	*full_path;
	char	*cmd_path;

	full_path = ft_strjoin(path_dir, "/");
	if (!full_path)
		return (NULL);
	cmd_path = ft_strjoin(full_path, cmd);
	free(full_path);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

static char	*path_env(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0 && ft_strlen(env[i]) > 5)
			path = env[i] + 5;
		i++;
	}
	if (!path)
		return (NULL);
	return (path);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	if (cmd && !cmd[0])
		return (NULL);
	cmd_path = try_direct_path(cmd);
	if (cmd_path || !env)
		return (ft_strdup(cmd_path));
	paths = ft_split(path_env(env), ':');
	if (!paths)
		paths = ft_split(get_mem()->env_path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		cmd_path = try_path(paths[i], cmd);
		if (cmd_path)
			return (free_split(paths), cmd_path);
	}
	free_split(paths);
	return (NULL);
}
