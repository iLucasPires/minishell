#include <minishell.h>

void handle_line(t_repl *data)
{
	if (data->line[0] != NULL_CHAR)
	{
		add_history(data->line);
		
		parser_and_tokenize(data->line, &data->head);
		show_list_linked(data->head);
	}
}

void	read_eval_print_loop(t_repl *data)
{
	while (true)
	{
		data->line = readline(PROMPT);
		handle_line(data);
		free_list_linked(&data->head);
		free(data->line);
	}
}
