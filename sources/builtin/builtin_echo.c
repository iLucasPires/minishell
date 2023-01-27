#include <minishell.h>

void	print_lists(t_list *tokens, int size)
{
	while (tokens && size > 0)
	{
		ft_putstr_fd(tokens->value, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		tokens = tokens->next;
		size--;
	}
}

int	builtin_echo(t_minishell *data, int size)
{
	t_list *token;

	token = data->tokens;
	if (token->next == NULL)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		if (ft_strncmp(token->next->value, "-n", 2) == 0)
			print_lists(token->next->next, size);
		else
		{
			print_lists(token->next, size);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	return (0);
}
