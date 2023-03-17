/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:35:00 by lucas             #+#    #+#             */
/*   Updated: 2023/01/24 01:57:51 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfjoin(char *string1, char *string2)
{
	char	*string_aux;

	if (string1 == NULL)
		return (string2);
	if (string2 == NULL)
		return (string1);
	string_aux = ft_strjoin(string1, string2);
	free(string1);
	free(string2);
	return (string_aux);
}
