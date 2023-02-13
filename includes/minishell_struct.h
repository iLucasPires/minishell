/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:35:20 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:57:39 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include <minishell.h>

typedef struct s_file
{
	int					fd;
	int					infile;
	int					outfile;
	char				*keepli;
}						t_file;

typedef struct s_token
{
	int					type;
	char				*value;
	struct s_token		*next;
}						t_list;

typedef struct s_clean_quote
{
	int					index;
	int					size;
	char				keep_quote;
	char				right;
	char				left;
	char				*line;
}						t_clean_quote;

typedef struct s_fsm
{
	int					index;
	int					limit;
	int					begin;
	int					check_quote;
	int					expand;
	int					act_squote;
	int					act_dquote;
	char				quote_type;
	char				*line;
	char				*line_aux;
	t_list				**tokens;
	t_list				*expanders;
}						t_fsm;

typedef struct s_executor
{
	int					status;
	int					count_cmd;
	int					**pipe;
	pid_t				*pid;
	int					aux_in;
	int					aux_out;
}						t_executor;

typedef struct s_command
{
	char				*pathname;
	char				**args;
	int					infile;
	int					outfile;
	struct s_command	*next;
}						t_command;

typedef struct s_repl
{
	char				*line;
	char				**paths;
	char				**envp;
	t_list				*envs;
	t_list				*tokens;
	t_list				*tokens_aux;
	u_int8_t			exit_code;
}						t_repl;

typedef struct s_minishell
{
	char				*line;
	char				**paths;
	char				**envp;
	char				*file_name;
	u_int8_t			exit_code;
	t_list				*envs;
	t_list				*tokens;
	t_list				*tokens_aux;
	t_executor			exec;
	t_command			*cmd_list;
}						t_minishell;

#endif