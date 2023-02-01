#include <minishell.h>

int	builtin_unset(char **args)
{
	int index;
	t_list *token_current;

	index = 1;
	while (args[index])
	{
		token_current = get_node(&g_data.envs, args[index]);
		if (token_current)
			delete_node(&g_data.envs, token_current);
		index++;
	}
	g_data.exit_code = 0;
	return (EXIT_SUCCESS);
}
