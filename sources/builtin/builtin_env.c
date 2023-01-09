#include <minishell.h>

int	builtin_env(t_minishell *data)
{
	t_list *token;

	token = data->envs;
	while (token)
	{
		if (token->type == TRUE)
			printf("%s \n", token->value);
		token = token->next;
	}
	return (EXIT_SUCCESS);
}