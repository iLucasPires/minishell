#include <minishell.h>

void	print_lists(t_list *tokens)
{
	while (tokens)
	{
		ft_putstr_fd(tokens->value, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		tokens = tokens->next;
	}
}

int	builtin_echo(t_minishell *data)
{
	t_list *token;

	token = data->tokens;
	if (token->next == NULL)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		if (ft_strncmp(token->next->value, "-n", 2) == 0)
			print_lists(token->next->next);
		else
		{
			print_lists(token->next);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	return (0);
}