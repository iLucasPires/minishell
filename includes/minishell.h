#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// libraries local
# include "../libft/includes/libft.h"
# include "./define.h"

enum				e_bool
{
	false,
	true
};

typedef struct s_fsmachine
{
	int				index;
	int				state;
	int				limit;
	char			*line;
	int				check_quote;
	char			quote_type;
}					t_fsmachine;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

// structs
typedef struct s_repl
{
	char			*line;
	int				status;
	char			**envp;
	char			**dirs;
	t_token			*head;
}					t_repl;

/*
Functions to be tested
*/

enum				e_type
{
	WORD,
	RED_IN,
	RED_OUT,
	RED_APPEND,
	HEREDOC,
	PIPE,
	QUOTE,
	N_EXPAND,
};

// prototypes
void				read_eval_print_loop(t_repl *data);
void				get_path(char *line);

// prototypes_error
void				error_generic(char *message);
void				error_pointer(char *message, void *pointer);
void				error_command(char *command);

// echo builtins
char				*echo_builtins(char *str, char *to_comp, int size);
void				parser_and_tokenize(char *str, t_token **head);

// prototypes_list_linked
t_token				*create_item(char *value, int type);
void				add_item_end(t_token **head, char *value, int type);
void				show_list_linked(t_token *head);
void				free_list_linked(t_token **head);
char				*next_item_list_linked(t_token **head);

// prototypes_parser_and_tokenize
int					is_state(char *str, int index);
int					is_space(char *str, int index);
int					is_special(char *str, int index);
void				finite_state_machine(char *str, t_token **head);

// prototypes_expansion
void				expansion(t_repl *data);

#endif