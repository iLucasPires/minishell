/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:35:29 by lucas             #+#    #+#             */
/*   Updated: 2023/02/13 16:03:12 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchar(char *string, char c)
{
	int		index;
	char	*string_temp;

	index = 1;
	string_temp = NULL;
	while (string[index] != '\0' && string[index] != c && string[index] != '\"'
		&& string[index] != '\'' && string[index] != ' ')
		index++;
	string_temp = calloc(index + 1, sizeof(char));
	ft_strlcpy(string_temp, string, index + 1);
	return (string_temp);
}
