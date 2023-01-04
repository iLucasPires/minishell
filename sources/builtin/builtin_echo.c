#include <minishell.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_putstr_fd(tokens->value, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		tokens = tokens->next;
	}
}

int	builtin_echo(t_repl *data)
{
	t_token *token;

	token = data->head;
	if (token->next == NULL)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		if (ft_strncmp(token->next->value, "-n", 2) == 0)
			print_tokens(token->next->next);
		else
		{
			print_tokens(token->next);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	return (0);
}