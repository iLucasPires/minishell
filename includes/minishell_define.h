#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define PROMPT BHBLACK "minishell " BHCYAN "$> " RESET

// error define
# define ERROR_ARGUMENTS "\033[1;31mminishell: too many arguments\033[0m\n"
# define ERROR_SYNTAX "\033[1;31mminishell: syntax error\033[0m\n"

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
