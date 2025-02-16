/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:46:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/16 18:48:11 by adoireau         ###   ########.fr       */
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
	char	**env;
	char	**cmd_tab;
	char	*cmd_path;
	char	*cmd;
	int		exit_status;
}	t_alloc;

char		*read_cmd(void);

void		bash_start(void);
void		cmd_not_found(char *cmd);

void		swap_env(char **env1, char **env2);
char		**dup_env(char **env);
char		**tmp_env(char **env);

char		*find_path(char *cmd, char **env);

int			env_cmd(char **env, char **arg);
void		env_no_such_file(char *arg);
void		env_invalid_option(char arg);
void		env_unrecognized_option(char *arg);
void		env_permission_denied(char *arg);

int			pwd_cmd(char **arg);
int			exit_cmd(char **arg);
int			export_cmd(t_alloc *mem, char **arg);
int			sort_export(char **env);
int			add_export(t_alloc *mem, char **arg);
int			unset_cmd(char **arg, char **env);

void		free_mem(t_alloc *mem);
t_alloc		*mem_exit(int err);
void		null_mem(t_alloc *mem);

#endif
