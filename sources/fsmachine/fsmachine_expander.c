/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsmachine_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:04 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 19:15:49 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fsm_expander_env(t_fsm *var, char *line)
{
	char	*line_aux;
	char	*line_aux2;

	line_aux = ft_strrchar(&line[var->index + 1], '$');
	line_aux2 = my_getenv(var->tokens, line_aux);
	var->line = ft_strfjoin(var->line, line_aux2);
	var->index += ft_strlen(line_aux);
	free(line_aux);
}

void	fsm_expander_word(t_fsm *expander, char *string)
{
	char	*string_aux;

	string_aux = NULL;
	if (expander->limit > 0)
	{
		expander->begin = expander->index - expander->limit;
		string_aux = ft_substr(string, expander->begin, expander->limit);
		expander->line = ft_strfjoin(expander->line, string_aux);
		expander->limit = 0;
	}
}

void	fsm_expander_dollar(t_fsm *var, char *line)
{
	if (line[var->index] == DOLLAR && line[var->index + 1] == '$')
		fsm_expander_special(var, ft_itoa(ft_getpid()));
	else if (line[var->index] == DOLLAR && line[var->index + 1] == '?')
		fsm_expander_special(var, ft_itoa(g_data.exit_code));
	else if (line[var->index] == DOLLAR)
	{
		if (line[var->index + 1] == NULL_CHAR || line[var->index + 1] == SPACE)
		{
			fsm_expander_special(var, ft_strdup("$"));
			var->index--;
		}
		else if (line[var->index + 1] == DQUOTE || line[var->index
				+ 1] == SQUOTE)
		{
			fsm_expander_special(var, ft_strdup("$"));
			var->index--;
		}
		else
			fsm_expander_env(var, line);
	}
}

void	fsm_expander_special(t_fsm *var, char *string)
{
	char	*string_aux;

	if (var->line == NULL)
	{
		var->line = string;
		var->index++;
		return ;
	}
	string_aux = var->line;
	var->line = ft_strjoin(var->line, string);
	var->index++;
	free(string_aux);
	free(string);
}

void	fsm_expander(char *line_temp, t_minishell *data)
{
	t_fsm	expander;

	ft_bzero(&expander, sizeof(t_fsm));
	expander.expand = TRUE;
	expander.tokens = &data->envs;
	fsm_expander_loop(&expander, line_temp);
}
