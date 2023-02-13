/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsmachine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:07 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 16:45:55 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fsm_is_inside_quote(t_fsm *fsm)
{
	if (fsm->line[fsm->index] == DQUOTE || fsm->line[fsm->index] == SQUOTE)
	{
		if (fsm->check_quote && fsm->line[fsm->index] == fsm->quote_type)
			fsm->check_quote = FALSE;
		else if (!fsm->check_quote)
		{
			fsm->check_quote = TRUE;
			fsm->quote_type = fsm->line[fsm->index];
		}
	}
}

void	fsm_filter_word(t_fsm *fsm, t_minishell *data)
{
	char	quote_char[2];

	if (fsm->limit > 0)
	{
		ft_strlcpy(quote_char, fsm->line + fsm->index - 1, 2);
		fsm->begin = fsm->index - fsm->limit;
		fsm->line_aux = ft_substr(fsm->line, fsm->begin, fsm->limit);
		if (ft_strchr(fsm->line_aux, DOLLAR))
			fsm_expander(fsm->line_aux, data);
		else if (*quote_char == DQUOTE || *quote_char == SQUOTE)
		{
			ft_rmchr(fsm->line_aux, quote_char);
			append_list(fsm->tokens, fsm->line_aux, WORD);
		}
		else
			append_list(fsm->tokens, fsm->line_aux, WORD);
		fsm->limit = 0;
		free(fsm->line_aux);
	}
}

void	fsm_filter_special(t_fsm *fsm)
{
	int	identifier;

	identifier = fsm_is_state(fsm->line, fsm->index);
	if (identifier == RED_IN || identifier == RED_OUT || identifier == PIPE)
		append_list(fsm->tokens, fsm_identified(identifier), identifier);
	if (identifier == RED_APPEND || identifier == HEREDOC)
	{
		append_list(fsm->tokens, fsm_identified(identifier), identifier);
		fsm->index++;
	}
}

void	finite_state_machine(t_minishell *data)
{
	t_fsm	fsm;

	ft_bzero(&fsm, sizeof(t_fsm));
	fsm.line = data->line;
	fsm.tokens = &data->tokens;
	while (TRUE)
	{
		fsm_is_inside_quote(&fsm);
		if (fsm_is_special(fsm.line, fsm.index) && !fsm.check_quote)
		{
			fsm_filter_word(&fsm, data);
			fsm_filter_special(&fsm);
		}
		else
			fsm.limit++;
		if (fsm.line[fsm.index] == NULL_CHAR)
			break ;
		fsm.index++;
	}
}
