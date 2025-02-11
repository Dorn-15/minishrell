/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:46:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 17:20:18 by adoireau         ###   ########.fr       */
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

typedef struct s_alloc
{
	//toutes les adresse des elements a potentielement free
	char	**env;
	char	**cmd_tab;
	char	*cmd_path;
	char	*cmd;
	int	exit_status;
}	t_alloc;

char		*read_cmd(void);

void		bash_start(void);
void		cmd_not_found(char *cmd);

char		**dup_env(char **env);

char		*find_path(char *cmd, char **env);

int		env_cmd(char **env, char **arg);
int		pwd_cmd(char **env, char *argm);
int		exit_cmd(char **arg);
void		free_mem(t_alloc *mem);
t_alloc	*mem_exit(int err);
void		null_mem(t_alloc *mem);

void		put_no_such_file(char *cmd, char *arg);
void		put_invalid_option(char *cmd, char arg);
void		put_unrecognized_option(char *cmd, char *arg);
void		put_permission_denied(char *cmd, char *arg);
#endif
