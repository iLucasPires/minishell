/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n <lpires-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:21:52 by lpires-n          #+#    #+#             */
/*   Updated: 2022/06/04 22:24:59 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	*ptr;
	int		space;

	space = nmemb * size;
	if (nmemb != 0 && space / size != nmemb)
		return (NULL);
	ptr = malloc(space);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, space);
	return (ptr);
}
