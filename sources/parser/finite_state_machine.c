#include <minishell.h>

char	*concatenate_string(char *string, char *string_aux)
{
	char	*string_temp;

	if (string == NULL)
		return (string_aux);
	if (string_aux == NULL)
		return (string);
	string_temp = ft_strjoin(string, string_aux);
	return (string_temp);
}

char	*get_string_until_char(char *string, char c)
{
	int		index;
	char	*string_temp;

	index = 1;
	string_temp = NULL;
	while (string[index] != NULL_CHAR && string[index] != c)
		index++;
	string_temp = calloc(index + 1, sizeof(char));
	ft_strlcpy(string_temp, string, index + 1);
	return (string_temp);
}

// void	fsm_expander(char **line_temp, char **temp, int (*index)[2],
// 		t_minishell *data)
// {
// 	char	*string_temp;
// 	char	*expanded_value;

// 	string_temp = NULL;
// 	expanded_value = NULL;
// 	if (*index[1] > 0)
// 	{
// 		string_temp = ft_substr(*line_temp, *index[0] - *index[1], *index[1]);
// 		*temp = concatenate_string(*temp, string_temp);
// 		*index[1] = 0;
// 	}
// 	string_temp = get_string_until_char(*line_temp + *index[0] + 1, '$');
// 	expanded_value = get_value_env(&data->envs, string_temp);
// 	*temp = concatenate_string(*temp, expanded_value);
// 	*index[0] += ft_strlen(string_temp);
// 	free(string_temp);
// }

// void	fsm_filter_expand(char *line_temp, t_minishell *data)
// {
// 	char	*temp;
// 	int		index[2];

// 	index[0] = 0;
// 	index[1] = 0;
// 	temp = NULL;
// 	while (TRUE)
// 	{
// 		if (line_temp[index[0]] == '$')
// 			fsm_expander(&line_temp, &temp, &index, data);
// 		else
// 			index[1]++;
// 		if (line_temp[index[0]] == NULL_CHAR)
// 		{
// 			new_node(&data->tokens, temp, WORD);
// 			break ;
// 		}
// 		index[0]++;
// 	}
// }

void	fsm_expander(char *string, t_minishell *data)
{
	char	*string_temp;
	char	*expanded_value;
	char	*temp;
	int		index;
	int		limit;

	index = 0;
	temp = NULL;
	limit = 0;
	expanded_value = NULL;
	string_temp = NULL;
	if (string == NULL || data == NULL)
		return ;
	while (TRUE)
	{
		if (string[index] == '$')
		{
			if (limit > 0)
			{
				string_temp = ft_substr(string, index - limit, limit);
				temp = concatenate_string(temp, string_temp);
				limit = 0;
			}
			string_temp = get_string_until_char(string + index + 1, '$');
			expanded_value = get_value_env(&data->envs, string_temp);
			temp = concatenate_string(temp, expanded_value);
			index += ft_strlen(string_temp);
			free(string_temp);
		}
		else
			limit++;
		if (string[index] == NULL_CHAR)
		{
			new_node(&data->tokens, temp, WORD);
			break ;
		}
		index++;
	}
}

void	fsm_filter_word(t_fsm *fsm, t_minishell *data)
{
	char	*line_temp;
	int		length;

	if (fsm->limit > 0)
	{
		length = fsm->index - fsm->limit;
		line_temp = ft_substr(fsm->line, length, fsm->limit);
		if (ft_strchr(line_temp, '$'))
			fsm_expander(line_temp, data);
		else
			new_node(&data->tokens, line_temp, WORD);
		fsm->limit = 0;
	}
}

void	fsm_filter_special(t_fsm *fsm, t_minishell *data)
{
	int	identifier;

	identifier = fsm_is_state(fsm->line, fsm->index);
	if (identifier == RED_IN || identifier == RED_OUT || identifier == PIPE)
	{
		new_node(&data->tokens, fsm_identified(identifier), identifier);
		fsm->index++;
	}
	if (identifier == RED_APPEND || identifier == HEREDOC)
	{
		new_node(&data->tokens, fsm_identified(identifier), identifier);
		fsm->index += 2;
	}
}

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

void	init_fsm(t_fsm *fsm, t_minishell *data)
{
	fsm->index = 0;
	fsm->limit = 0;
	fsm->begin = 0;
	fsm->check_quote = FALSE;
	fsm->quote_type = 0;
	fsm->line = data->line;
}

void	finite_state_machine(t_minishell *data)
{
	t_fsm	fsm;

	init_fsm(&fsm, data);
	while (TRUE)
	{
		fsm_is_inside_quote(&fsm);
		if (fsm_is_special(fsm.line, fsm.index) && !fsm.check_quote)
		{
			fsm_filter_word(&fsm, data);
			fsm_filter_special(&fsm, data);
		}
		else
			fsm.limit++;
		if (fsm.line[fsm.index] == NULL_CHAR)
			break ;
		fsm.index++;
	}
}
