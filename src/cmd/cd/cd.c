/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:00:28 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/09 14:17:20 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
bash: cd: (arg): File name too long
*/
static int	cd_chdir(t_alloc *mem, char *path)
{
	int	err;

	err = 0;
	if (chdir(path) == -1)
	{
		if (errno == EACCES)
			err = cd_permission_denied(path);
		else if (errno == ELOOP || errno == EMLINK)
			err = cd_too_many_links(path);
		else if (errno == ENOENT)
			err = cd_no_such_file(path);
		else if (errno == ENOTDIR)
			err = cd_not_a_directory(path);
		else
			err = cd_no_such_file(path);
	}
	else
		cd_update_env(mem);
	return (err);
}

static int	cd_home(t_alloc *mem)
{
	char	*home;
	int		err;

	home = cd_getenv("HOME", mem->env);
	if (!home)
		return (cd_home_not_set());
	if (!*home)
	{
		cd_update_oldpwd(mem);
		free(home);
		return (0);
	}
	err = cd_chdir(mem, home);
	free(home);
	return (err);
}

static int	cd_oldpwd(t_alloc *mem)
{
	char	*oldpwd;
	int		err;

	oldpwd = cd_getenv("OLDPWD", mem->env);
	if (!oldpwd)
		return (cd_oldpwd_not_set());
	if (!*oldpwd)
	{
		cd_update_oldpwd(mem);
		free(oldpwd);
		write(1, "\n", 1);
		return (0);
	}
	err = cd_chdir(mem, oldpwd);
	if (err == 0)
		printf("%s\n", oldpwd);
	free(oldpwd);
	return (err);
}

static int	cd_tilde(t_alloc *mem, char *arg)
{
	int		err;
	char	*home;
	char	*tmp;

	err = 0;
	home = cd_getenv("HOME", mem->env);
	if (!home)
		return (cd_home_not_set());
	tmp = ft_strjoin(home, arg + 1);
	err = cd_chdir(mem, tmp);
	free(tmp);
	free(home);
	return (err);
}

int	cd_cmd(t_alloc *mem, char **arg)
{
	int	err;

	err = 0;
	if (!arg || !*arg)
		return (1);
	else if (!arg[1] || (arg[1] && !arg[1][0]))
		return (cd_home(mem));
	else if (arg[1][0] == '-' && arg[1][1] != '\0')
		return (cd_invalid_option(arg[1][1]));
	else if (arg[2])
		return (cd_to_many_arg());
	else if (arg[1][0] == '-')
		return (cd_oldpwd(mem));
	else if (arg[1][0] == '~')
		return (cd_tilde(mem, arg[1]));
	err = cd_chdir(mem, arg[1]);
	return (err);
}
