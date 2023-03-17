/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:39:53 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:07:19 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	syntax_error_redirects(char *file_name)
{
	if (file_name == NULL)
		return (TRUE);
	if (!ft_strcmp(file_name, "<") || !ft_strcmp(file_name, "<<") || \
		!ft_strcmp(file_name, ">") || !ft_strcmp(file_name, ">>") || \
		!ft_strcmp(file_name, "|"))
		return (TRUE);
	return (FALSE);
}

int	open_files(int type, char *file_name, t_command *cmd, t_minishell *data)
{
	if (cmd == NULL || syntax_error_redirects(file_name))
	{
		ft_putstr_fd("No such file or directory\n", 2);
		data->exit_code = 2;
		return (TRUE);
	}
	else if (type == HEREDOC)
		make_heredoc(cmd, file_name, data);
	else if (type == RED_IN)
		cmd->infile = open_file(file_name, O_RDONLY, 0, &data->exit_code);
	else if (type == RED_OUT)
		cmd->outfile = open_file(file_name, R_FLAG, 0644, &data->exit_code);
	else if (type == RED_APPEND)
		cmd->outfile = open_file(file_name, A_FLAG, 0644, &data->exit_code);
	free(file_name);
	return (EXIT_SUCCESS);
}

void	check_redirected(t_minishell *data, t_command *cmd)
{
	t_list	*aux;

	aux = data->tokens;
	while (aux != NULL)
	{
		if (aux->type == PIPE)
			cmd = cmd->next;
		if (is_redirect(aux->type) != FALSE && cmd->infile != -1 && \
			cmd->outfile != -1)
		{
			if (aux->next == NULL || aux->next->type != DOCUMENT)
			{
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				cmd->infile = FAILURE;
				data->exit_code = 2;
				return ;
			}
			data->file_name = ft_strdup(aux->next->value);
			open_files(aux->type, data->file_name, cmd, data);
		}
		aux = aux->next;
	}
}
