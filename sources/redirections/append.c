#include <minishell.h>

void make_append(t_list *token, t_minishell *data)
{
	(void)data;
	data->file.outfile = open(token->next->value, O_CREAT | O_RDWR | O_APPEND , 0664);
	if (data->file.outfile == -1)
		dprintf(2, "ERROR na MAKEAPPEND\n");
}