#include <minishell.h>

int	builtin_unset(char **args, t_minishell *data)
{
	int index;
	t_list *token_current;

	index = 1;
	while (args[index])
	{
		token_current = get_node(&data->envs, args[index]);
		if (token_current)
			delete_node(&data->envs, token_current);
		index++;
	}
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}
