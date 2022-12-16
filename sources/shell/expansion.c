#include <minishell.h>

void	expansion(t_repl *data)
{
	t_token *temp_head;
	char *temp;

	temp_head = data->head;
	while (temp_head != NULL)
	{
		if (temp_head->type == WORD)
		{
			if (temp_head->value[0] == '$')
			{
				ft_strlcpy(temp_head->value, temp_head->value + 1, ft_strlen(temp_head->value));
				temp = getenv(temp_head->value);
				free(temp_head->value);
				temp_head->value = ft_strdup(temp);
			}
		}
		temp_head = temp_head->next;
	}
}