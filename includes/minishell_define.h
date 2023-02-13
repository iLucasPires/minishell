/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:57 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:57:12 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

// error define
# define ERROR_ARGUMENTS "\033[1;31mminishell: too many arguments\033[0m\n"
# define ERROR_SYNTAX "\033[1;31mminishell: syntax error\033[0m\n"
# define ERROR_EXIT "\033[1;31mexit: too many arguments\033[0m\n"
# define ERROR_EXIT_CODE "\033[1;31mexit: numeric argument required\033[0m\n"

# define TOKENS_VIEW "%.*s= \" %s\"\n"

//process define
# define FAILURE -1
# define SUCCESS 0
# define CHILD 0
# define INVISIBLE_CHAR -1
# define A_FLAG 1090
# define R_FLAG 578

// token define

# define SDQUOTE "\""
# define DQUOTE '\"'
# define SQUOTE '\''
# define BSLASH '\\'
# define PLUSTHAN '>'
# define LESSTHAN '<'
# define BAR '|'
# define NULL_CHAR '\0'
# define DOLLAR '$'
# define TILDE '~'
# define EQUAL '='
# define UNDERSCORE '_'
# define HERE_FILE "./tmp_file"

#endif
