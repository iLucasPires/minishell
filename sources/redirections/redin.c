#include <minishell.h>

// <

int make_input(char *file_name, int flags)
{
    int fd;

    fd = open(file_name, flags);
    if (fd == -1)
        dprintf(2, "bash: %s: No such file or directory\n", file_name);
    return (fd);
}

int make_output(char *file_name, int flags)
{
    int fd;

    fd = open(file_name, flags, 0644);
    if (fd == -1)
        dprintf(2, "bash: %s: No such file or directory\n", file_name);
    return (fd);
}
