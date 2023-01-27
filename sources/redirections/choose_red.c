#include <minishell.h>

// 1	RED_IN <
// 2	RED_OUT >
// 3	RED_APPEND >>
// 4	HEREDOC <<

static int choose_red(t_list *token, t_minishell *data, int *fd);

void check_red(t_minishell *data, int *fd)
{
    t_list *aux;

    aux = data->tokens_aux;
    while (aux)
    {
        if (aux->next->type > 0 && aux->next->type < 5)
        {
            choose_red(aux->next, data, fd);
            aux = aux->next;
        }
        else
        {
            if(aux->next)
                aux = aux->next;
        }
    }
}

static int choose_red(t_list *token, t_minishell *data, int *fd)
{
    if (token->type == 4)
    {
        if (!token->next)
            return (ft_putstr_fd(ERROR_SYNTAX, 2), 1);
        make_heredoc(token, data, fd);
    }
    else if (token->type == 3)
    {
        if (!token->next)
            return (ft_putstr_fd(ERROR_SYNTAX, 2), 1);
        make_append(token, data);
    }
    else if (token->type == 2)
    {
        if (!token->next)
            return (ft_putstr_fd(ERROR_SYNTAX, 2), 1);
        make_output(token ,data);

    }
    else if (token->type == 1)
    {
        if (!token->next)
            return (ft_putstr_fd(ERROR_SYNTAX, 2), 1);
        make_input(token, data);
    }
    return (0);
}
