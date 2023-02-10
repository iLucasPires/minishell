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

extern t_minishell	g_data;

// prototypes
void				read_eval_print_loop(t_minishell *data);
int					syntax_quotes(char *line);
int					system_command(t_minishell *data);
int					syntax_error_pipe(t_list *tokens);
// prototypes_signal
void				handle_sigint(int signum);
void				handle_sigquit(t_minishell *data);

// exec_builtins
int					builtin_cd(char **args, t_minishell *data);
int					builtin_echo(char **args, t_minishell *data);
int					builtin_pwd(char **args, t_minishell *data);
int					builtin_exit(char **args, t_minishell *data);
int					builtin_env(char **args, t_minishell *data);
int					builtin_export(char **args, t_minishell *data);
int					builtin_unset(char **args, t_minishell *data);

// prototypes_list_linked
void				new_node(t_list **head, char *value, int type);
void				destroy_list(t_list **head);

void				delete_node(t_list **head, t_list *item);
t_list				*get_node(t_list **head, char *target);
char				*get_value(t_list **head, char *target);
char				*my_getenv(t_list **head, char *target);
void				add_env(t_list **env, char *value);
void				substitute_env(t_list *token_current, char *value);
void				delete_just_node(t_list **head, t_list *item);

// prototypes_parser_and_tokenize
int					fsm_is_state(char *str, int index);
int					fsm_is_space(char *str, int index);
int					fsm_is_special(char *str, int index);
char				*fsm_identified(int identifier);
void				finite_state_machine(t_minishell *data);
void				expander_word(t_fsm *expander, char *string);
void				expander_dollar(t_fsm *expander, char *string);

int					ft_lstlen(t_list *lst);
int					ft_lstnlen(t_list *lst, int target);
int					ft_lsttlen(t_list *lst, int target);

// free prototypes
void				destroy_minishell(t_minishell *data);
void				destroy_repl(t_minishell *data);
void				destroy_exit_minishell(t_minishell *data, int status);
void				free_all(char **pointer);

// here_doc
void				check_redirected(t_minishell *data, t_command *cmd);
int					make_output(char *file_name, int flags);
int					make_input(char *file_name, int flags);
int					count_pipes(t_list *tokens);
void				make_heredoc(t_command *cmd, char *file_name,
						t_minishell *data);

// prototypes_exec
char				*get_path_command(t_list *list, char **paths);
char				**list_to_array_string(t_list *list);
char				**create_arguments(t_list *list);
t_command			*create_cmd_list(t_minishell *data);
void				destroy_cmd_list(t_command *cmd_list);
int					is_redirect(int identifier);

// prototypes_message
void	message_command_not_found(char *command,
								u_int8_t *exit_code);

int					exec_builtins(char **args, t_minishell *data);
int					is_builtin(char *str);

void				dup_fds(t_command *cmd);
void				dup_saved_fds(int saved[2]);
void				close_fds(t_command *cmd);
void				close_saved_fds(int saved[2]);
pid_t				my_getpid(void);
void				ft_lstadd_back(t_command **list_cmd, t_minishell *data);
void				dup_pipe_fds(t_minishell *cmd, int child_index);
void				close_pipe_fds(t_minishell *cmd, int child_index);
void				destroy_executor(t_minishell *data);

void				make_redirects(t_command *cmd, int child_index,
						t_minishell *data);
void				builtin_redirect(t_command *cmd);
void				init_resources(t_command *cmd, t_minishell *data);
void				reset_int_out(t_minishell *data);
void				close_files(t_command *cmd);
void				execute_builtin_child(t_command *cmd, t_minishell *data,
						int child_index);
int					open_file(char *file, int flags, int other_flags,
						u_int8_t *exit_code);
#endif
