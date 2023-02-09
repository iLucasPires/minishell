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

void typing_tokens(t_list *tokens)
{
	t_list	*aux;

	aux = tokens;
	while (aux)
	{
		if (is_redirect(aux->type))
		{
			if (aux->next && aux->next->type == WORD)
				aux->next->type = DOCUMENT;
		}
		aux = aux->next;
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
			typing_tokens(data->tokens);
			if (data->tokens->value)
				data->exit_code = system_command(data);
			destroy_list(&data->tokens);
		}
	}
}

void	read_eval_print_loop(t_minishell *data)
{
	// char	path[1024];

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (TRUE)
	{
		// getcwd(path, 1024);
		// ft_strlcat(path, "\n", 1024);
		// printf(BHGREEN "%s" RESET, path);
		data->line = readline("minishell> ");
		handle_line(data);
		free(data->line);
	}
	exit(EXIT_SUCCESS);
}
