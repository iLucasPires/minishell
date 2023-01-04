#include <minishell.h>

int	builtin_env(t_repl *data)
{
	t_token *token;

	token = data->env;
	while (token)
	{
		if (token->type == true)
			printf("%s \n", token->value);
		token = token->next;
	}
	return (EXIT_SUCCESS);
}