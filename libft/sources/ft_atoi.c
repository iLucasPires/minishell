/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  lpires-n < lpires-n@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:41:31 by lpires-n          #+#    #+#             */
/*   Updated: 2022/11/15 03:00:22 by  lpires-n        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	signal;
	int	result;

	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == ' '))
		nptr++;
	signal = ((ft_isdigit(*nptr) || *nptr == '+') - (*nptr == '-'));
	nptr += (*nptr == '-' || *nptr == '+');
	while (ft_isdigit(*nptr))
		result = result * 10 + (*nptr++ - '0');
	return (result * signal);
}
