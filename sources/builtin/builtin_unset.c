#include <minishell.h>

int	builtin_unset(t_minishell *data)
{
	t_list *temp;
	t_list *token_current;

	temp = data->tokens;
	while (temp->next)
	{
		token_current = get_node(&data->envs, temp->next->value);
		if (token_current != NULL)
			delete_node(&data->envs, token_current);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}