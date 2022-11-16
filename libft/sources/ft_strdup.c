/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n <lpires-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:50:19 by lpires-n          #+#    #+#             */
/*   Updated: 2022/06/09 23:37:49 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*s1;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	s1 = (char *)malloc((len + 1) * sizeof(char));
	ft_memcpy(s1, s, len + 1);
	return (s1);
}
