/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:35:29 by lucas             #+#    #+#             */
/*   Updated: 2023/01/27 01:53:26 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchar(char *string, char c)
{
	int index;
	char *string_temp;

	index = 1;
	string_temp = NULL;
	while (string[index] != '\0' && string[index] != c && string[index] != '\"'
		&& string[index] != '\'' && string[index] != ' ')
		index++;
	string_temp = calloc(index + 1, sizeof(char));
	ft_strlcpy(string_temp, string, index + 1);
	return (string_temp);
}