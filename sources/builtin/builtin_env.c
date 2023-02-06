#include <minishell.h>

int	builtin_env(char **args, t_minishell *data)
{
	t_list *token_current;

	token_current = data->envs;
	if (args[1] == NULL)
	{
		while (token_current)
		{
			if (token_current->type == TRUE)
			{
				ft_putstr_fd(token_current->value, STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
			}
			token_current = token_current->next;
		}
	}
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}