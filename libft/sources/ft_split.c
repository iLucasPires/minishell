/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n <lpires-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:23:10 by lpires-n          #+#    #+#             */
/*   Updated: 2022/06/10 19:38:38 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_string(char const *s, char c)
{
	int	i;
	int	n_word;
	int	control;

	i = 0;
	control = 0;
	n_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && control == 0)
		{
			control = 1;
			n_word++;
		}
		else if (s[i] == c)
			control = 0;
		i++;
	}
	return (n_word);
}

static void	add_string(char const *s, char c, char **split)
{
	size_t	len;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	len = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (i != len)
			{
				split[j] = ft_substr(s, len, i - len);
				if (split[j] == NULL)
					free(split);
				j++;
			}
			len = i + 1;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;

	i = count_string(s, c);
	split = malloc(sizeof(char *) * (i + 1));
	if (split == NULL)
		return (NULL);
	add_string(s, c, split);
	split[i] = NULL;
	return (split);
}
