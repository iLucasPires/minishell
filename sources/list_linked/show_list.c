#include <minishell.h>

void	show_list_linked(t_list **head)
{
	t_list	*tokens;

	tokens = *head;
	while (tokens)
	{
		ft_putstr_fd(BHWHITE, STDOUT_FILENO);
		ft_putstr_fd(tokens->value, STDOUT_FILENO);
		ft_putstr_fd(RESET "\n", STDOUT_FILENO);
		tokens = tokens->next;
	}
}

void	show_list_linked_filter(t_list **head, int type)
{
	t_list *tokens;

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