/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:46:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/17 16:39:36 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_alloc
{
	//toutes les adresse des elements a potentielement free
	char	**cmd_tab;
	char	*cmd_path;
	char	*cmd;
	char	**env;
	char	oldpwd[PATH_MAX];
	int	exit_status;
}	t_alloc;

char		*read_cmd(void);

void		bash_start(void);
void		cmd_not_found(char *cmd);

void		swap_env(char **env1, char **env2);
char		**dup_env(char **env);
char		**tmp_env(char **env);
int		new_var_env(t_alloc *mem, char *arg, int i);

char		*find_path(char *cmd, char **env);

int		env_cmd(char **env, char **arg);
void		env_no_such_file(char *arg);
void		env_invalid_option(char arg);
void		env_unrecognized_option(char *arg);
void		env_permission_denied(char *arg);

int		pwd_cmd(char **arg);
int		exit_cmd(char **arg);
int		unset_cmd(char **arg, char **env);

int		export_cmd(t_alloc *mem, char **arg);
int		sort_export(char **env);
int		add_export(t_alloc *mem, char **arg);


int		cd_cmd(t_alloc *mem, char **arg);
void		cd_update_env(t_alloc *mem);
void		cd_update_oldpwd(t_alloc *mem);
char		*cd_getenv(char *name, char **env);
int		cd_invalid_option(char c);
int		cd_to_many_arg();
int		cd_home_not_set();
int		cd_oldpwd_not_set();
int		cd_permission_denied(char *arg);
int		cd_too_many_links(char *arg);
int		cd_no_such_file(char *arg);
int		cd_not_a_directory(char *arg);
int		cd_oldpwd(t_alloc *mem);

void		free_mem(t_alloc *mem);
t_alloc		*mem_exit(int err);
void		null_mem(t_alloc *mem);

#endif
