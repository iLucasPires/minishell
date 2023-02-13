#include <minishell.h>

char *rm_char_index(char *str, int position);

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

void	fsm_clean_quote(t_fsm *expander)
{
	int	index;
	int size_line;
	char keep_quote;
	char left;
	char right;

	index = 0;
	size_line = ft_strlen(expander->line);
	left = 0;
	right = 0;
	keep_quote = 0;
	while (index < size_line)
	{
		if (expander->line[index] == SQUOTE || expander->line[index] == DQUOTE)
		{
			right = DQUOTE;
			left = expander->line[index];
			if (left == DQUOTE)
				right = SQUOTE;
		}
		if (expander->line[index] == left && keep_quote != right)
		{
			if (keep_quote == left)
			{
				keep_quote = 0;
				expander->line = rm_char_index(expander->line, index);
				index--;
				size_line--;
			}
			else
			{
				keep_quote = left;
				expander->line = rm_char_index(expander->line, index);
				index--;
				size_line--;
			}
		}
		index++;
	}
}

char *rm_char_index(char *str, int position)
{
	char *new_str;
	int new_index;
	int index;

	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	index = 0;
	new_index = 0;
	while(str[new_index])
	{
		if(position == index)
			index++;
		new_str[new_index] = str[index];
		index++;
		new_index++;
	}
	free(str);
	return(new_str);
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

