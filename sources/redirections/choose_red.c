#include <minishell.h>

// 1	RED_IN <
// 2	RED_OUT >
// 3	RED_APPEND >>
// 4	HEREDOC <<

static int syntax_error_redirects(char *file_name)
{
    if (file_name == NULL)
        return (1);
    if (!ft_strcmp(file_name, "<") || !ft_strcmp(file_name, "<<") || !ft_strcmp(file_name, ">") || !ft_strcmp(file_name, ">>") ||
    !ft_strcmp(file_name, "|"))
        return (1);
    return (0);
}

int open_files(int type, char *file_name, t_command **cmd)
{
    if (syntax_error_redirects(file_name))
        return (ft_putstr_fd("ERROR NA OPEN FILES\n", 2), 1);
    else if (type == HEREDOC)
        make_heredoc(cmd, file_name);
    else if (type == RED_IN)
        (*cmd)->infile = make_input(file_name, (O_RDONLY));
    else if (type == RED_OUT)
        (*cmd)->outfile = make_output(file_name, (O_CREAT | O_RDWR | O_TRUNC));
    else if (type == RED_APPEND)
        (*cmd)->outfile = make_output(file_name, (O_CREAT | O_RDWR | O_APPEND));
    return (0);
}

void    check_red(t_list *token, t_command *cmd)
{
    while (token)
    {
        if (token->type == PIPE)
            cmd = cmd->next;
        if (is_redirect(token->type))
            open_files(token->type, token->next->value, &cmd);
        token = token->next;
    }
}
