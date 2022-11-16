/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  lpires-n < lpires-n@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:57:28 by lpires-n          #+#    #+#             */
/*   Updated: 2022/11/15 03:15:19 by  lpires-n        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char	*string;
	int		i;

	i = 0;
	string = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (string == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		string[i] = f(i, str[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}
