#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

// libraries local
# include <define.h>
# include <libft.h>

enum e_bool
{
	false,
	true
};

// structs
typedef struct s_repl
{
	char	*line;
	int		status;
	char	**envp;
	char	**dirs;
}			t_repl;

typedef struct s_command
{
	char	*name;
	char	*path;
	char	**args;
}			t_command;

// prototypes
void		read_eval_print_loop(t_repl *data);
void		get_path(char *line);
#endif