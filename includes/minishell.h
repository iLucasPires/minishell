#ifndef MINISHELL_H
# define MINISHELL_H

// libraries


# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

// libraries local
# include <define.h>
# include <libft.h>

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

// prototypes
void		read_eval_print_loop(t_repl *repl);
void	get_path(char *line);
#endif