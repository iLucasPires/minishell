/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:53:31 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 16:05:54 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export_add(t_minishell *data, char *value)
{
	if (ft_isalnum(*value) || *value == UNDERSCORE)
	{
		if (ft_strchr(value, EQUAL) != NULL)
			append_list(&data->envs, value, TRUE);
		else
			append_list(&data->envs, value, FALSE);
		data->exit_code = 0;
	}
	else
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		data->exit_code = 1;
	}
}

void	export_update(t_list *token_current, char *value)
{
	if (ft_strchr(value, EQUAL) != NULL)
	{
		free(token_current->value);
		token_current->value = ft_strdup(value);
		if (token_current->type == FALSE)
			token_current->type = TRUE;
	}
}
