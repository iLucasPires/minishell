#include <minishell.h>

static int	syntax_error_redirects(char *file_name)
{
	if (file_name == NULL)
		return (TRUE);
	if (!ft_strcmp(file_name, "<") || !ft_strcmp(file_name, "<<") ||
		!ft_strcmp(file_name, ">") || !ft_strcmp(file_name, ">>") ||
		!ft_strcmp(file_name, "|"))
		return (TRUE);
	return (FALSE);
}

int	open_files(int type, char *file_name, t_command *cmd, t_minishell *data)
{
	if (cmd == NULL)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		data->exit_code = 2;
		
	}
	if (syntax_error_redirects(file_name))
	{
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": syntax error near unexpected token\n", 2);
		data->exit_code = 2;
		return (1);
	}
	else if (type == HEREDOC)
		make_heredoc(cmd, file_name, data);
	else if (type == RED_IN)
		cmd->infile = make_input(file_name, (O_RDONLY));
	else if (type == RED_OUT)
		cmd->outfile = make_output(file_name, (O_CREAT | O_RDWR | O_TRUNC));
	else if (type == RED_APPEND)
		cmd->outfile = make_output(file_name, (O_CREAT | O_RDWR | O_APPEND));
	return (0);
}

void	check_redirected(t_minishell *data, t_command *cmd)
{
	t_list	*aux;
	char	*file_name;

	aux = data->tokens;
	while (aux != NULL)
	{
		if (aux->type == PIPE)
			cmd = cmd->next;
		if (is_redirect(aux->type) != FALSE)
		{
			file_name = ft_strdup(aux->next->value);
			open_files(aux->type, file_name, cmd, data);
			free(file_name);
		}
		aux = aux->next;
	}
}
