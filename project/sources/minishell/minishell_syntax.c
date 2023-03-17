/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:33 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:05:34 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	syntax_quotes(char *line)
{
	int	index;
	int	value;

	index = 0;
	value = 0;
	while (line[index] != NULL_CHAR)
	{
		if (line[index] == SQUOTE || line[index] == DQUOTE)
		{
			value = line[index];
			index++;
			while (line[index] && line[index] != value)
				index++;
			if (line[index] == NULL_CHAR)
			{
				ft_putstr_fd(ERROR_SYNTAX, 2);
				return (EXIT_FAILURE);
			}
		}
		index++;
	}
	return (EXIT_SUCCESS);
}

int	syntax_error_pipe(t_list *tokens)
{
	if (tokens->type == PIPE)
		return (ft_putstr_fd(ERROR_SYNTAX, 2), 2);
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (tokens->next == NULL)
				return (ft_putstr_fd(ERROR_SYNTAX, 2), 2);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
