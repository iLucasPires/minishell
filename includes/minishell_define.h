#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define PROMPT "\033[1;32mminishell\033[0m$ "
# define MAX_LINE 80

// error define
# define ERROR_ARGUMENTS "\033[1;31mminishell: too many arguments\033[0m\n"
# define ERROR_READLINE "\033[1;31mminishell: readline error\033[0m\n"
# define ERROR_GENERIC "\033[1;31mminishell: error\033[0m\n"
# define ERROR_MALLOC "\033[1;31mminishell: malloc error\033[0m\n"
# define ERROR_SYNTAX "\033[1;31mminishell: syntax error\033[0m\n"
# define ERROR_EXECVE "\033[1;31mminishell: execve failed\033[0m\n"
# define ERROR_COMMAND "\033[1;31mminishell: %s: command not found\033[0m\n"
# define ERROR_EXIT "\033[1;31mminishell: exit\033[0m\n"

# define TOKENS_VIEW "%.*s= \" %s\"\n"

//process define
# define FAILURE -1
# define INVISIBLE_CHAR -1

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

// heredoc define

# define HERE_FILE	"./tmp_file"

#endif