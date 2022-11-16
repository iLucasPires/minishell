/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  lpires-n < lpires-n@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:15:59 by lpires-n          #+#    #+#             */
/*   Updated: 2022/11/15 03:15:53 by  lpires-n        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

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
