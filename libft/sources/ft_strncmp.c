/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n <lpires-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:59:11 by lpires-n          #+#    #+#             */
/*   Updated: 2022/06/04 06:50:50 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	index;
	unsigned int	value;

	index = 0;
	value = 0;
	while (index < n)
	{
		if (str1[index] == str2[index] && str1[index] != '\0')
			value = (unsigned char)str1[index] - (unsigned char)str2[index];
		else
		{
			value = (unsigned char)str1[index] - (unsigned char)str2[index];
			break ;
		}
		index++;
	}
	return (value);
}
