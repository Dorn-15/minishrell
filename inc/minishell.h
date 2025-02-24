/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:46:55 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/24 17:01:36 by adoireau         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

extern int	g_sign;

typedef enum s_token
{
	cmd_cpt,
	pipe_cpt,
	in_op,
	out_op,
	here_doc_op,
	append_op,
	limiter,
	fd_in_cpt,
	fd_out_cpt,
	append_out,
	initialized,
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	char			**limiter;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_alloc
{
	char	*line;
	char	**env;
	char	oldpwd[PATH_MAX];
	int		exit_status;
	t_cmd	*cmd;
	char	*cmd_path;
	int		stdinstock;
	int		stdoutstock;
}	t_alloc;

//read_right
char		*read_cmd(void);
void		bash_start(void);
void		cmd_not_found(char *cmd);

//env_utils
void		swap_env(char **env1, char **env2);
char		**dup_env(char **env);
char		**tmp_env(char **env);
int			new_var_env(t_alloc *mem, char *arg, int i);

//find_path
char		*find_path(char *cmd, char **env);

//env_cmd
int			env_cmd(char **env, char **arg);
void		env_no_such_file(char *arg);
void		env_invalid_option(char arg);
void		env_unrecognized_option(char *arg);
void		env_permission_denied(char *arg);

//other_cmd
int			pwd_cmd(char **arg);
int			exit_cmd(char **arg, int exit_status);
int			unset_cmd(char **arg, char **env);
int			echo_cmd(char **arg);

//export_cmd
int			export_cmd(t_alloc *mem, char **arg);
int			sort_export(char **env);
int			add_export(t_alloc *mem, char **arg);

//cd_cmd
int			cd_cmd(t_alloc *mem, char **arg);
void		cd_update_env(t_alloc *mem);
void		cd_update_oldpwd(t_alloc *mem);
int			cd_oldpwd(t_alloc *mem);
char		*cd_getenv(char *name, char **env);

//cd_error
int			cd_invalid_option(char c);
int			cd_to_many_arg(void);
int			cd_home_not_set(void);
int			cd_oldpwd_not_set(void);
int			cd_permission_denied(char *arg);
int			cd_too_many_links(char *arg);
int			cd_no_such_file(char *arg);
int			cd_not_a_directory(char *arg);

//free
void		free_mem(t_alloc *mem);
void		mem_exit(int err);
void		null_mem(t_alloc *mem);
t_alloc		*get_mem(void);

//Exec
void		here_doc(t_alloc *mem);
void		child_process(t_alloc *mem);
void		multiple_pipe(t_alloc *mem);
void		change_fd(t_alloc *mem, int pip_fd[2]);
int			try_builtins(t_alloc *mem);

//Clear
char		*clear_param(char *str);
char		*error_clear(char *str);

//Lexer
char		*lexer(char **split_arg);
char		**lex_split(char *str, t_alloc *mem);
char		**ft_freetab(char **dest);
int			count_tab(char**tab);
char		*clear_word(char *str);

//Parsing
t_cmd		*parsing_list(char *tk_str, char **split_arg);
t_cmd		*launch_pars(t_alloc *mem);
t_cmd		*error_pars(int n, char **split_arg, char *tk_str, t_alloc *mem);
t_cmd		*fd_handler(char *tk_str, char **arg, int i, t_cmd *new_cmd);
t_cmd		*check_special_case(t_cmd *list, t_cmd *tmp, t_alloc *mem);
char		**limiter_setting(char *tk_str, char **arg, int i);
int			count_cmd(char *tk_str, int i, char n);

//Expand
char		*expand(const char *str, t_alloc *mem);
char		*search_expand_utils(const char *str, int *i, int *j, t_alloc *mem);
char		*expand_getenv(char *name, char **env);
char		*tmp_create(const char *str, char **exp);
int			is_expand(const char *str);
int			expand_size(const char *str);

//List
t_cmd		*ft_lstclear_pars(t_cmd **list);

//Signal
void		setup_parent_signals(void);
void		setup_child_signals(void);
void		setup_heredoc_signals(void);
void		setup_parent_fork(void);
#endif
