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
# include "./minishell_struct.h"
# include "./minishell_enum.h"

extern t_minishell	g_minishell;

// prototypes
void					read_eval_print_loop(t_minishell *data);
void					syntax_quotes(char *line);
int						system_command(t_minishell *data);

// prototypes_signal
void					handle_sigint(int signum);
void					handle_sigquit(t_minishell *data);

// builtins
int						builtin_cd(t_command **cmd);
int						builtin_echo(char **args);
int						builtin_pwd(t_minishell *data);
int						builtin_exit(t_minishell *data);
int						builtin_env(t_executor **exec);
int						builtin_export(t_minishell *data);
int						builtin_unset(t_minishell *data);

// prototypes_list_linked
void					new_node(t_list **head, char *value, int type);
void					destroy_list(t_list **head);

void					delete_node(t_list **head, t_list *item);
t_list					*get_node(t_list **head, char *target);
char					*get_value(t_list **head, char *target);
char					*my_getenv(t_list **head, char *target);
void					add_env(t_list **env, char *value);
void					substitute_env(t_list *token_current, char *value);
void					delete_just_node(t_list **head, t_list *item);

// prototypes_parser_and_tokenize
int						fsm_is_state(char *str, int index);
int						fsm_is_space(char *str, int index);
int						fsm_is_special(char *str, int index);
char					*fsm_identified(int identifier);
void					finite_state_machine(t_minishell *data);
void					expander_word(t_fsm *expander, char *string);
void					expander_dollar(t_fsm *expander, char *string,
							t_list **envs);

int						ft_lstlen(t_list *lst);
int						ft_lstnlen(t_list *lst, int target);
int						ft_lsttlen(t_list *lst, int target);

// free prototypes
void					destroy_minishell(t_minishell *data);
void					destroy_repl(t_minishell *data);
void					destroy_exit_minishell(t_minishell *data, int status);
void					free_all(char **pointer);

// here_doc
void					check_red(t_list *token, t_command *cmd);
int						make_output(char *file_name, int flags);
int						make_input(char *file_name, int flags);
int						count_pipes(t_list *tokens);

// prototypes_exec
char					*get_path_command(t_list *list, char **paths);
char					**list_to_array_string(t_list *list);
char					**create_arguments(t_list *list);
t_command				**build_list(t_minishell *data);
int						is_redirect(int identifier);

// prototypes_message
void					message_command_not_found(t_list *tokens);

// TESTER BUILTIN
int						builtins(t_command **cmd, t_executor **exec);
int						pwd(void);
int						is_builtin(char *str);

pid_t	my_getpid(void);
#endif