#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

// libraries local
# include <define.h>
# include "../libft/includes/libft.h"

enum			e_bool
{
	false,
	true
};

// structs
typedef struct s_repl
{
	char		*line;
	int			status;
	char		**envp;
	char		**dirs;
}				t_repl;

typedef struct s_command
{
	char		*command_name;
	char		*path;
	char		**args;
	enum e_bool	is_valid;
}				t_command;

// prototypes
void			read_eval_print_loop(t_repl *data);
void			get_path(char *line);

// prototypes_error
void			error_generic(char *message);
void			error_pointer(char *message, void *pointer);
void			error_command(char *command);
#endif