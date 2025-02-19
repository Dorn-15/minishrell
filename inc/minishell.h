/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: altheven <altheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:46:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/19 12:07:49 by altheven         ###   ########.fr       */
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


typedef enum s_token{
	cmd_cpt,
	pipe_cpt,
	in_op,
	out_op,
	here_doc_op,
	append_op,
	limiter,
	fd_in_cpt,
	fd_out_cpt,
	initialized,
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	char			*limiter;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_alloc
{
	//toutes les adresse des elements a potentielement free
	char	**cmd_tab;
	char	*cmd_path;
	char	*cmd;
	char	**env;
	char	oldpwd[PATH_MAX];
	int		exit_status;
}	t_alloc;

char		*read_cmd(void);

void		bash_start(void);
void		cmd_not_found(char *cmd);

void		swap_env(char **env1, char **env2);
char		**dup_env(char **env);
char		**tmp_env(char **env);
int			new_var_env(t_alloc *mem, char *arg, int i);

char		*find_path(char *cmd, char **env);

int			env_cmd(char **env, char **arg);
void		env_no_such_file(char *arg);
void		env_invalid_option(char arg);
void		env_unrecognized_option(char *arg);
void		env_permission_denied(char *arg);

int			pwd_cmd(char **arg);
int			exit_cmd(char **arg);
int			unset_cmd(char **arg, char **env);
int			echo_cmd(char **arg);

int			export_cmd(t_alloc *mem, char **arg);
int			sort_export(char **env);
int			add_export(t_alloc *mem, char **arg);

int			cd_cmd(t_alloc *mem, char **arg);
void		cd_update_env(t_alloc *mem);
void		cd_update_oldpwd(t_alloc *mem);
char		*cd_getenv(char *name, char **env);
int			cd_invalid_option(char c);
int			cd_to_many_arg(void);
int			cd_home_not_set(void);
int			cd_oldpwd_not_set(void);
int			cd_permission_denied(char *arg);
int			cd_too_many_links(char *arg);
int			cd_no_such_file(char *arg);
int			cd_not_a_directory(char *arg);
int			cd_oldpwd(t_alloc *mem);

void		free_mem(t_alloc *mem);
t_alloc		*mem_exit(int err);
void		null_mem(t_alloc *mem);

//Clear

char		*clear_param(char *str);
char		*error_clear(char *str);

//Lexer
char		*lexer(char **split_arg);
char		**lex_split(char *str, char **envp);
char		**ft_freetab(char **dest);
int			count_tab(char**tab);
char		*clear_word(char *str);

//Parsing

t_cmd		*parsing_list(char *tk_str, char **split_arg);
t_cmd		*launch_pars(t_alloc *mem);

//Expand
char		*expand(const char *str, char **envp);
int			is_expand(const char *str);

//List

t_cmd		*ft_lstclear_pars(t_cmd **list);

#endif
