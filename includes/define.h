#ifndef DEFINE_H
# define DEFINE_H

# define PROMPT "\033[1;32mminishell\033[0m$ "
# define HERE_FILE "./tmp_file"
# define MAX_LINE 80

// color define
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

// error define
# define ERROR_ARGUMENTS "\033[1;31mminishell: too many arguments\033[0m\n"
# define ERROR_READLINE "\033[1;31mminishell: readline error\033[0m\n"
# define ERROR_GENERIC "\033[1;31mminishell: error\033[0m\n"
# define ERROR_MALLOC "\033[1;31mminishell: malloc error\033[0m\n"
# define ERROR_SYNTAX "\033[1;31mminishell: syntax error: unexpected end of file\033[0m\n"
# define ERROR_EXECVE "\033[1;31mminishell: execve failed\033[0m\n"
# define ERROR_COMMAND "\033[1;31mminishell: %s: command not found\033[0m\n"

#define TOKENS_VIEW "value: %s, type: %d\n"

//process define
# define CHILD_PROCESS 0
# define EXE_FALL -1
# define NO_ACCESS -1
# define INVISIBLE_CHAR -1

#define DQUOTE '\"'
#define SQUOTE '\''
#define BSLASH '\\'
#define PLUSTHAN '>'
#define LESSTHAN '<'
#define BAR '|'
#define NULL_CHAR '\0'
#define DOLLAR '$'

#endif