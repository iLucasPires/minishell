#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// libraries local
# include "../libft/includes/libft.h"
# include "./minishell_colors.h"
# include "./minishell_define.h"
# include "./minishell_enum.h"
# include "./minishell_struct.h"
# include "./minishell_prototypes.h"

extern t_minishell	g_data;


#endif
