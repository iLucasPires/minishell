/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsmachine_expander_aux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:02 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:36:21 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*rm_char_index(char *str, int position);

void	fsm_expander_squote(t_fsm *expander, char *line_temp)
{
	if (line_temp[expander->index] == SQUOTE)
	{
		if (expander->act_squote == TRUE)
		{
			expander->act_squote = FALSE;
			expander->expand = TRUE;
			return ;
		}
		if (expander->act_dquote == TRUE)
			return ;
		expander->act_squote = TRUE;
		expander->expand = !expander->expand;
	}
}

void	fsm_expander_dquote(t_fsm *expander, char *line_temp)
{
	if (line_temp[expander->index] == DQUOTE)
	{
		if (expander->act_dquote == TRUE)
		{
			expander->act_dquote = FALSE;
			return ;
		}
		if (expander->act_squote == TRUE)
			return ;
		expander->act_dquote = TRUE;
		expander->expand = TRUE;
	}
}

void	fsm_expander_quote(t_fsm *expander, char *line_temp)
{
	if (line_temp[expander->index] == DQUOTE
		|| line_temp[expander->index] == SQUOTE)
	{
		fsm_expander_squote(expander, line_temp);
		fsm_expander_dquote(expander, line_temp);
	}
}

void	fsm_clean_quote(t_fsm *exp)
{
	t_clean_quote	var;

	ft_bzero(&var, sizeof(t_clean_quote));
	var.size = ft_strlen(exp->line);
	while (var.index < var.size)
	{
		if (exp->line[var.index] == SQUOTE || exp->line[var.index] == DQUOTE)
		{
			var.right = DQUOTE;
			var.left = exp->line[var.index];
			if (var.left == DQUOTE)
				var.right = SQUOTE;
		}
		if (exp->line[var.index] == var.left && var.keep_quote != var.right)
		{
			if (var.keep_quote == var.left)
				var.keep_quote = 0;
			else
				var.keep_quote = var.left;
			exp->line = rm_char_index(exp->line, var.index);
			var.index--;
			var.size--;
		}
		var.index++;
	}
}

char	*rm_char_index(char *str, int position)
{
	char	*new_str;
	int		new_index;
	int		index;

	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	index = 0;
	new_index = 0;
	while (str[new_index])
	{
		if (position == index)
			index++;
		new_str[new_index] = str[index];
		index++;
		new_index++;
	}
	free(str);
	return (new_str);
}
