#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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
}			t_repl;

typedef struct s_data
{
	char	**envp;
	t_repl	repl;
}			t_data;

typedef struct s_command
{
	char	*name;
	char	*path;
	char	**args;
	struct s_command *next;
}			t_command;

// prototypes
void		read_eval_print_loop(t_repl *repl);
void		get_path(char *line);
#endif