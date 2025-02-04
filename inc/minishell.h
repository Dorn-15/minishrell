#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

char	*read_cmd(void);
void	bash_start(void);
char	*find_path(char *cmd, char **env);

#endif
