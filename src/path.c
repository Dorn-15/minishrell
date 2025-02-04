/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:51:32 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/04 11:56:31 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*try_direct_path(char *cmd)
{
	if (!cmd)
		return (NULL);
	if ((cmd[0] == '/' || cmd[0] == '.') && access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

char	*get_path_string(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

char	*try_path(char *path_dir, char *cmd)
{
	char	*full_path;
	char	*cmd_path;

	full_path = ft_strjoin(path_dir, "/");
	if (!full_path)
		return (NULL);
	cmd_path = ft_strjoin(full_path, cmd);
	free(full_path);
	if (cmd_path && access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	cmd_path = try_direct_path(cmd);
	if (cmd_path || !env)
		return (cmd_path);
	paths = ft_split(get_path_string(env), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = try_path(paths[i], cmd);
		if (cmd_path)
		{
			free_split(paths);
			return (cmd_path);
		}
		i++;
	}
	free_split(paths);
	return (NULL);
}
