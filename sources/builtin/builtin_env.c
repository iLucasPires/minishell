#include <minishell.h>

int	builtin_env(t_executor **exec)
{
	int i;

	i = 0;
	while ((*exec)->envp_array[i])
	{
		if ((*exec)->envp_array[i])
			printf("%s\n", (*exec)->envp_array[i]);
		i++;;
	}
	return (EXIT_SUCCESS);
}