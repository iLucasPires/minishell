/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 03:31:47 by lpires-n          #+#    #+#             */
/*   Updated: 2022/12/14 21:14:07 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*str;

	begin = 0;
	if (!s1 || !set)
		return (NULL); 
	while (*s1 && ft_strchr(set, s1[begin]))
		begin++;
	end = ft_strlen(s1);
	while (end && ft_strchr(set, s1[end]))
		end--;
	str = ft_substr(s1, begin, end - begin + 1);
	return (str);
}
