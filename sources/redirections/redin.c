#include <minishell.h>

// <

int make_input(char *file_name, int flags)
{
    int fd;

    fd = open(file_name, flags);
    if (fd == -1)
    {
        perror("open");
        g_data.exit_code = 1;
    }
    return (fd);
}

int make_output(char *file_name, int flags)
{
    int fd;

    fd = open(file_name, flags, 0644);
    if (fd == -1)
    {
        perror("open");
        g_data.exit_code = 2;
    }
    return (fd);
}
