#include <minishell.h>

int	builtin_unset(t_repl *data)
{
	t_token *temp;
	t_token *token_current;

	temp = data->head;
	while (temp->next)
	{
		token_current = get_node_list_linked(&data->env, temp->next->value);
		if (token_current != NULL)
			free_item(&data->env, token_current);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}