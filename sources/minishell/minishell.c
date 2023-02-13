#include <minishell.h>

char	*remove_space(char *line)
{
	int		index;
	char	*new_line;

	index = 0;
	while (line[index] == SPACE)
		index++;
	if (line[index] == NULL_CHAR)
	{
		free(line);
		return (NULL);
	}
	new_line = ft_substr(line, index, ft_strlen(line));
	free(line);
	return (new_line);
}

void	typing_tokens(t_list *tokens)
{
	t_list	*token_temp;

	token_temp = tokens;
	if (tokens == NULL)
		return ;
	while (token_temp != NULL)
	{
		if (is_redirect(token_temp->type))
		{
			if (token_temp->next && token_temp->next->type == WORD)
				token_temp->next->type = DOCUMENT;
		}
		token_temp = token_temp->next;
	}
}

void print_tokens(t_list *tokens)
{
	t_list	*token_temp;

	token_temp = tokens;
	if (tokens == NULL)
		return ;
	while (token_temp != NULL)
	{
		printf("type: %d, value: %s	\n", token_temp->type, token_temp->value);
		token_temp = token_temp->next;
	}
	printf("\n");
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

			print_tokens(data->tokens);
			// if (data->tokens->value)
			// 	data->exit_code = system_command(data);
			destroy_list(&data->tokens);
		}
	}
}

void	read_eval_print_loop(t_minishell *data)
{
	while (TRUE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		data->line = readline(PROMPT);
		handle_line(data);
		free(data->line);
	}
	exit(EXIT_SUCCESS);
}
