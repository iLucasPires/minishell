#include "minishell.h"

int	fsm_is_state(char *str, int index)
{
	if (str[index] == PLUSTHAN)
	{
		if (str[index + 1] == PLUSTHAN)
			return (RED_APPEND);
		return (RED_OUT);
	}
	else if (str[index] == LESSTHAN)
	{
		if (str[index + 1] == LESSTHAN)
			return (HEREDOC);
		return (RED_IN);
	}
	else if (str[index] == BAR)
		return (PIPE);
	else
		return (FALSE);
}

int	fsm_is_space(char *str, int index)
{
	if (str[index] == SPACE || str[index] == NULL_CHAR)
		return (TRUE);
	return (FALSE);
}

int	fsm_is_special(char *str, int index)
{
	if (fsm_is_state(str, index) || fsm_is_space(str, index))
		return (TRUE);
	return (FALSE);
}

char	*fsm_identified(int identifier)
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
