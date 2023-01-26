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

enum				e_bool
{
	FALSE,
	TRUE
};

typedef struct s_file
{
	int				fd;
	char			*keepli;
}					t_file;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}					t_list;

typedef struct s_fsm
{
	int				index;
	int				limit;
	int				begin;
	int				check_quote;
	char			quote_type;
	char			*line;
	t_list			**tokens;
	t_list			*expanders;
}					t_fsm;

typedef struct s_expander
{
	int				index;
	int				limit;
	int				begin;
	char			*line;
	t_list			**tokens;
}					t_expander;

typedef struct s_command
{
	char	*cmd;
	char	**args;
	char	**envp;
}					t_command;

// structs
typedef struct s_minishell
{
	int			pipefd[2];
	pid_t		pid;
	int			status;
	char		*line;
	char		*home;
	char		**paths;
	t_file		file;
	t_list		*envs;
	t_list		*tokens;
	t_list		*tokens_aux;
}					t_minishell;

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
void	read_eval_print_loop(t_minishell *data);
void	choose_command(t_minishell *data);
void	syntax_quotes(char *line);

// prototypes_signal
void	handle_sigint(int signum);
void	handle_sigquit(t_minishell *data);

// builtins
int		builtin_cd(t_minishell *data);
int		builtin_echo(t_minishell *data);
int		builtin_pwd(t_minishell *data);
int		builtin_exit(t_minishell *data);
int		builtin_env(t_minishell *data);
int		builtin_export(t_minishell *data);
int		builtin_unset(t_minishell *data);

// prototypes_list_linked
void	new_node(t_list **head, char *value, int type);
void	destroy_list(t_list **head);

void	delete_node(t_list **head, t_list *item);
t_list	*get_node(t_list **head, char *target);
char	*get_value(t_list **head, char *target);
char	*my_getenv(t_list **head, char *target);
void	add_env(t_list **env, char *value);
void	substitute_env(t_list *token_current, char *value);
void	delete_just_node(t_list **head, t_list *item);

// prototypes_parser_and_tokenize
int		fsm_is_state(char *str, int index);
int		fsm_is_space(char *str, int index);
int		fsm_is_special(char *str, int index);
char	*fsm_identified(int identifier);
void	finite_state_machine(t_minishell *data);
void	expander_word(t_expander *expander, char *string);
void	expander_dollar(t_expander *expander, char *string, t_list **envs);

int		ft_lstlen(t_list *lst);
int		ft_lstnlen(t_list *lst, int target);
int		ft_lsttlen(t_list *lst, int target);
// free prototypes
void	destroy_minishell(t_minishell *data);
void	destroy_repl(t_minishell *data);
void	destroy_exit_minishell(t_minishell *data, int status);
void	free_all(char **pointer);

// here_doc
void	make_heredoc(t_minishell *data);

// prototypes_exec
char	*get_path_command(t_list *list, char **paths);
char	**list_to_array_string(t_list *list);
char	**create_arguments(t_list **list);
int		destroy_command(t_command *cmd);
int		create_command(t_command *cmd, t_minishell *data);
// prototypes_message
void	message_command_not_found(t_list *tokens);

#endif