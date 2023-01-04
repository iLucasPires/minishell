#include <minishell.h>

void	show_list_linked(t_token **head)
{
	t_token	*tokens;

	tokens = *head;
	while (tokens)
	{
		ft_putstr_fd(BHWHITE, STDOUT_FILENO);
		ft_putstr_fd(tokens->value, STDOUT_FILENO);
		ft_putstr_fd(RESET "\n", STDOUT_FILENO);
		tokens = tokens->next;
	}
}

void	show_list_linked_filter(t_token **head, int type)
{
	t_token *tokens;

	tokens = *head;
	while (tokens)
	{
		if (tokens->type == type)
		{
			ft_putstr_fd(BHWHITE, STDOUT_FILENO);
			ft_putstr_fd(tokens->value, STDOUT_FILENO);
			ft_putstr_fd(RESET "\n", STDOUT_FILENO);
		}
		tokens = tokens->next;
	}
}