/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:15:59 by lpires-n          #+#    #+#             */
/*   Updated: 2022/12/27 00:48:27 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	len;
	size_t	res;

	len = ft_strlen(str2);
	if (str2[0] == '\0')
		return ((char *)str1);
	while (*str1 && (n-- >= len))
	{
		res = ft_strncmp(str1, str2, len);
		if (res == 0 && *str1 == *str2)
			return ((char *)str1);
		str1++;
	}
	return (NULL);
}
