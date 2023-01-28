#include <minishell.h>

char	*remove_space(char *string)
{
	int		index;
	char	*string_aux;

	index = 0;
	while (string[index] == SPACE)
		index++;
	if (string[index] == NULL_CHAR)
	{
		free(string);
		return (NULL);
	}
	string_aux = ft_substr(string, index, ft_strlen(string));
	free(string);
	return (string_aux);
}

void print_list(t_list *list)
{
	while (list)
	{
		printf("token: %s\n", list->value);
		list = list->next;
	}
}

void	handle_line(t_minishell *data)
{
	handle_sigquit(data);
	if (*data->line)
	{
		add_history(data->line);
  		data->line = remove_space(data->line);
		if (data->line && data->line[0] != SPACE)
		{
			syntax_quotes(data->line);
			finite_state_machine(data);
			system_command(data);
			// print_list(data->tokens);
			destroy_list(&data->tokens);
		}
	}
}

void	read_eval_print_loop(t_minishell *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (TRUE)
	{
		data->line = readline(BHBLUE "minishell$> " RESET);
		handle_line(data);
		free(data->line);
	}
	exit(EXIT_SUCCESS);
}
