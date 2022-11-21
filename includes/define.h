#ifndef DEFINE_H
# define DEFINE_H

# define PROMPT "\033[1;32mminishell\033[0m$ "
# define MAX_LINE 80

// error define
# define ERROR_ARGUMENTS "\033[1;31mminishell: too many arguments\033[0m\n"
# define ERROR_READLINE "\033[1;31mminishell: readline error\033[0m\n"
# define ERROR_GENERIC "\033[1;31mminishell: error\033[0m\n"
# define ERROR_EXECVE "\033[1;31mminishell: execve failed\033[0m\n"
# define ERROR_COMMAND "\033[1;31mminishell: %s: command not found\033[0m\n"

//process define
# define CHILD_PROCESS 0
# define EXE_FALL -1
# define NO_ACCESS -1
# define INVISIBLE_CHAR -1

#endif