#include "libft.h"

char	*ft_chrtstr(char c)
{
	char *str;

	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	str[1] = '\0';

	return (str);
}