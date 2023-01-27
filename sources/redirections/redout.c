#include <minishell.h>

void make_output(t_list *token, t_minishell *data)
{
	int fd;

	(void)data;
	fd = open(token->next->value, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd == -1)
		dprintf(2, "ERROR na MAKEOUTPUT!\n");
    dup2(fd, STDOUT_FILENO);
	close (fd);
}
