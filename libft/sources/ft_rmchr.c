#include "libft.h"

void	ft_rmchr(char *str, char *targets)
{
	int	current_index;
	int	target_index;

	current_index = 0;
	target_index = 0;
	while (str[current_index])
	{
		if (!ft_strchr(targets, str[current_index]))
		{
			str[target_index] = str[current_index];
			target_index++;
		}
		current_index++;
	}
	str[target_index] = '\0';
}
