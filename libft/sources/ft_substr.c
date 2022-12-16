/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:28:08 by lpires-n          #+#    #+#             */
/*   Updated: 2022/12/15 00:25:52 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	len_max;
	size_t	size;

	size = ft_strlen(s);
	len_max = size - start;
	if (s == NULL)
		return (NULL);
	if (start > size)
	{
		len = 1;
		start = 0;
	}
	else if (start + len > size)
		len = len_max + 1;
	else
		len = len + 1;
	s1 = malloc(len);
	if (s1 == NULL)
		return (NULL);
	ft_strlcpy(s1, s + start, len);
	return (s1);
}
