/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n <lpires-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:33:00 by lpires-n          #+#    #+#             */
/*   Updated: 2022/06/04 06:53:15 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	crt;

	str = (unsigned char *)s;
	crt = (unsigned char)c;
	if (!n)
		return (NULL);
	while (n-- && *str != crt)
		str++;
	if (crt == *str)
		return (str + n);
	return (NULL);
}
