/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 19:21:38 by lucas             #+#    #+#             */
/*   Updated: 2023/01/01 19:22:08 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
    int	index;
    int	value;

    index = 0;
    value = 0;
    while (str1[index] == str2[index] && str1[index] != '\0')
        index++;
    value = (unsigned char)str1[index] - (unsigned char)str2[index];
    return (value);
}