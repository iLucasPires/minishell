#include <minishell.h>

void	filter_special(t_token **head, t_fsmachine *fsm)
{
	int		begin;
	int		result;
	char	*string;

	begin = fsm->index - fsm->limit;
	result = is_state(fsm->line, fsm->index);
	if (fsm->limit > 0)
	{
		string = ft_substr(fsm->line, begin, fsm->limit);
		add_item_end(head, string, WORD);
		fsm->limit = 0;
	}
	if (result == RED_IN || result == RED_OUT || result == PIPE)
	{
		string = ft_substr(fsm->line, fsm->index, 1);
		add_item_end(head, string, result);
	}
	if (result == RED_APPEND || result == HEREDOC)
	{
		string = ft_substr(fsm->line, fsm->index, 2);
		add_item_end(head, string, result);
		fsm->index++;
	}
}

void	is_inside_quote(t_fsmachine *fsm)
{
	if (fsm->line[fsm->index] == DQUOTE || fsm->line[fsm->index] == SQUOTE)
	{
		if (fsm->check_quote && fsm->line[fsm->index] == fsm->quote_type)
			fsm->check_quote = false;
		else if (!fsm->check_quote)
		{
			fsm->check_quote = true;
			fsm->quote_type = fsm->line[fsm->index];
		}
	}
}

void	finite_state_machine(char *str, t_token **head)
{
	t_fsmachine	fsm;

	fsm = (t_fsmachine){0, 0, 0, str, false, ' '};
	while (true)
	{
		is_inside_quote(&fsm);
		if (is_special(fsm.line, fsm.index) && !fsm.check_quote)
			filter_special(head, &fsm);
		else
			fsm.limit++;
		if (str[fsm.index++] == NULL_CHAR)
			break ;
	}
}
