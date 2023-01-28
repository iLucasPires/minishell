#include <minishell.h>

int	builtin_echo(char **args)
{
	int cmpr;
	int i;

	i = 1;
	if (args[1] == NULL)
		return(printf("\n"), 0);
	cmpr = ft_strcmp(args[1], "-n");
	if (cmpr == 0)
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (cmpr != 0)
		printf("\n");
	return (0);
}
