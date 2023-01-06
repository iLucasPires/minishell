/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:08:30 by lucas             #+#    #+#             */
/*   Updated: 2023/01/04 14:07:19 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strtlen(const char *str, char c)
{
	size_t len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}
// string mamaco="put"
// mamaco2=