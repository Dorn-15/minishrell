/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:46:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 10:10:14 by adoireau         ###   ########.fr       */
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
}	t_alloc;

char		*read_cmd(void);

void		bash_start(void);
void		cmd_not_found(char *cmd);

char		**dup_env(char **env);

char		*find_path(char *cmd, char **env);

void		env_cmd(char **env);
void		pwd_cmd(char **env, char *argm);
void		exit_cmd(char **arg);
void		free_mem(t_alloc *mem);
t_alloc	*mem_exit(int err);
void		null_mem(t_alloc *mem);


#endif
