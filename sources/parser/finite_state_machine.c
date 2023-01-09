#include <minishell.h>

char	*identified_type(int identifier)
{
	if (identifier == RED_IN)
		return ("<");
	if (identifier == RED_OUT)
		return (">");
	if (identifier == PIPE)
		return ("|");
	if (identifier == RED_APPEND)
		return (">>");
	if (identifier == HEREDOC)
		return ("<<");
	return ("");
}

void	fsm_filter_special(t_fsm *fsm, char *line, t_list **tokens)
{
	int	identifier;

	identifier = fsm_is_state(line, fsm->index);
	if (identifier == RED_IN || identifier == RED_OUT || identifier == PIPE)
	{
		new_node(tokens, identified_type(identifier), identifier);
		fsm->index++;
	}
	if (identifier == RED_APPEND || identifier == HEREDOC)
	{
		new_node(tokens, identified_type(identifier), identifier);
		fsm->index += 2;
	}
}

void	fsm_filter_word(t_fsm *fsm, char *line, t_list **tokens)
{
	char	*string;
	int		length;

	if (fsm->limit > 0)
	{
		length = fsm->index - fsm->limit;
		string = ft_substr(line, length, fsm->limit);
		new_node(tokens, string, WORD);
		fsm->limit = 0;
		free(string);
	}
}

void	fsm_is_inside_quote(t_fsm *fsm, char *line)
{
	if (line[fsm->index] == DQUOTE || line[fsm->index] == SQUOTE)
	{
		if (fsm->check_quote && line[fsm->index] == fsm->quote_type)
			fsm->check_quote = FALSE;
		else if (!fsm->check_quote)
		{
			fsm->check_quote = TRUE;
			fsm->quote_type = line[fsm->index];
		}
	}
}

void	init_fsm(t_fsm *fsm)
{
	fsm->index = 0;
	fsm->limit = 0;
	fsm->begin = 0;
	fsm->check_quote = FALSE;
	fsm->quote_type = 0;
}

void	finite_state_machine(t_minishell *data)
{
	t_fsm	fsm;

	init_fsm(&fsm);
	while (TRUE)
	{
		fsm_is_inside_quote(&fsm, data->line);
		if (fsm_is_special(data->line, fsm.index) && !fsm.check_quote)
		{
			fsm_filter_word(&fsm, data->line, &data->tokens);
			fsm_filter_special(&fsm, data->line, &data->tokens);
		}
		else
			fsm.limit++;
		if (!data->line[fsm.index++])
			break ;
	}
}
