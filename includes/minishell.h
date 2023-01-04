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
# include "./colors.h"
# include "./define.h"

typedef struct s_file
{
	char			*keepli;
	int				fd;
}					t_file;

enum				e_bool
{
	false,
	true
};

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_fsmachine
{
	int				index;
	int				limit;
	int				begin;
	int				check_quote;
	char			quote_type;
	t_token			**head;
}					t_fsmachine;

// structs
typedef struct s_repl
{
	char			*line;
	char			*home;
	char			*path;
	t_token			*env;
	t_token			*head;
	int				status;
	t_file			file;
}					t_repl;

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
	EXPAND,
};

// prototypes
void				path_current(t_repl *data);
void				read_eval_print_loop(t_repl *data);
void				get_path(char *line);
void				verify_command(t_repl *data);
void				verify_quotes(char *line);

// prototypes_error
void				error_generic_with_arg(char *message, char *arg);
void				error_generic(char *message);
void				error_command(char *command);
void				error_malloc(char *message, void *ptr);

// prototypes_signal
void				handle_sigint(int signum);
void				handle_sigquit(t_repl *data);

// echo builtins
int					builtin_cd(t_repl *data);
int					builtin_echo(t_repl *data);
int					builtin_pwd(t_repl *data);
int					builtin_exit(t_repl *data);
int					builtin_env(t_repl *data);
int					builtin_export(t_repl *data);
int					builtin_unset(t_repl *data);

// prototypes_list_linked
void				add_item_end(t_token **head, char *value, int type);
void				free_list_linked(t_token **head);

char				*next_item_list_linked(t_token **head);
void				free_item(t_token **head, t_token *item);
void				show_list_linked_filter(t_token **head, int type);
void				show_list_linked(t_token **head);
t_token				*get_node_list_linked(t_token **head, char *value);
char				*get_value_list_linked(t_token **head, char *value);
char				*get_value_env(t_token **head, char *value);

// prototypes_parser_and_tokenize
int					is_state(char *str, int index);
int					is_space(char *str, int index);
int					is_special(char *str, int index);
void				finite_state_machine(char *str, t_token **head);

// prototypes_expansion
void				expansion(t_repl *data);

// free prototypes
void				free_minishell(t_repl *data);
void				free_repl(t_repl *data);
void				free_exit_minishell(t_repl *data, int status);

// here_doc
void				make_heredoc(t_file *file, t_token *list);
void				write_in_file(t_file *file, t_token *list);

#endif