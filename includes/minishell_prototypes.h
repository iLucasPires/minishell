/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prototypes.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:35:32 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 16:01:46 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTOTYPES_H
# define MINISHELL_PROTOTYPES_H

void		read_eval_print_loop(t_minishell *data);
int			syntax_quotes(char *line);
int			system_command(t_minishell *data);
int			syntax_error_pipe(t_list *tokens);

void		handle_sigint(int signum);
void		handle_sigquit(t_minishell *data);

// builtins prototypes
int			builtin_cd(char **args, t_minishell *data);
int			builtin_echo(char **args, t_minishell *data);
int			builtin_pwd(char **args, t_minishell *data);
int			builtin_exit(char **args, t_minishell *data);
int			builtin_env(char **args, t_minishell *data);
int			builtin_export(char **args, t_minishell *data);
int			builtin_unset(char **args, t_minishell *data);

// builtins utils prototypes
void		export_add(t_minishell *data, char *value);
void		export_update(t_list *token_current, char *value);

//parser prototypes
void		finite_state_machine(t_minishell *data);
void		fsm_expander(char *line_temp, t_minishell *data);
void		fsm_clean_quote(t_fsm *expander);
void		fsm_expander_quote(t_fsm *expander, char *line_temp);
void		fsm_expander_special(t_fsm *var, char *string);
void		fsm_expander_env(t_fsm *var, char *line);

//executor prototypes
void		destroy_pathname_not_found(t_minishell *data, int child_index);
void		execute_builtin(t_command *cmd, t_minishell *data);
void		create_executor(t_minishell *data);

void		append_list(t_list **head, char *value, int type);
void		destroy_list(t_list **head);

void		delete_node(t_list **head, t_list *item);
t_list		*get_node(t_list **head, char *target);
char		*get_value(t_list **head, char *target);
char		*my_getenv(t_list **head, char *target);

int			fsm_is_state(char *str, int index);
int			fsm_is_space(char *str, int index);
int			fsm_is_special(char *str, int index);
char		*fsm_identified(int identifier);
void		finite_state_machine(t_minishell *data);
void		fsm_expander_word(t_fsm *expander, char *string);
void		fsm_expander_dollar(t_fsm *expander, char *string);

int			ft_lstlen(t_list *lst);
int			ft_lstnlen(t_list *lst, int target);
int			ft_lsttlen(t_list *lst, int target);

void		destroy_minishell(t_minishell *data);
void		destroy_repl(t_minishell *data);
void		destroy_exit_minishell(t_minishell *data, int status);
void		free_all(char **pointer);

void		check_redirected(t_minishell *data, t_command *cmd);
int			make_output(char *file_name, int flags);
int			make_input(char *file_name, int flags);
void		make_heredoc(t_command *cmd, char *file_name, t_minishell *data);

char		*get_path_command(t_list *list, char **paths);
char		**list_to_array_string(t_list *list);
char		**create_arguments(t_list *list);
t_command	*create_cmd_list(t_minishell *data);
void		destroy_cmd_list(t_command *cmd_list);
int			is_redirect(int identifier);

int			exec_builtins(char **args, t_minishell *data);
int			is_builtin(char *str);

void		dup_fds(t_command *cmd);
void		close_fds(t_command *cmd);
pid_t		ft_getpid(void);
void		ft_lstadd_back(t_command **list_cmd, t_minishell *data);
void		close_pipe_fds(t_executor *exec, int child_index);
void		destroy_executor(t_executor *exec, t_list *tokens);

void		make_redirects(t_command *cmd, int child_index, t_executor *exec);
void		close_files(t_command *cmd);
void		destroy_execute_system(t_minishell *data);
void		execute_builtin_child(t_command *cmd, t_minishell *data,
				int child_index);
int			open_file(char *file, int flags, int other_flags,
				u_int8_t *exit_code);

#endif