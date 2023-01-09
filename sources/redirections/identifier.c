#include <minishell.h>

// Type dentro do t_list;
// type recebe o tipo do argumento
// type input = 1;
// type output = 2;
// type append = 3;
// type heredoc = 4;

int check_redirection(t_minishell *data)
{
    // if (data->tokens->type == 1 && data->tokens->next->value)
    // {
    //     input_red(&data);
    //     return (data->tokens->type);
    // }
    // else if (data->tokens->type == 2)
    // {
    //     output_red(&data);
    //     return (data->tokens->type);
    // }
    // else if (data->tokens->type == 3)
    // {
    //     append_red(&data);
    //     return (data->tokens->type);
    // }
    if (data->tokens->type == 4 && data->tokens->next->value)
    {
        make_heredoc(data);
        return (data->tokens->type);
    }
    else
        return (0);
}