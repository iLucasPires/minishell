/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  lpires-n < lpires-n@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:48:52 by lpires-n          #+#    #+#             */
/*   Updated: 2022/11/15 03:13:14 by  lpires-n        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t size;
	char	*str;
	
	
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(size * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (*s1)
		str[len++] = *s1++;
	while (*s2)
		str[len++] = *s2++;
	str[len] = '\0';
	return (str);
}
