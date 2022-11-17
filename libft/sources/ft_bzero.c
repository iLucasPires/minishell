/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  lpires-n < lpires-n@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:15:01 by lpires-n          #+#    #+#             */
/*   Updated: 2022/11/16 21:14:44 by  lpires-n        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t size)
{
	char	*str;
	size_t	index;

	index = 0;
	str = (char *)ptr;
	while (size--)
	{
		str[index] = '\0';
		index++;
	}
}
