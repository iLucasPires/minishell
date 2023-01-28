#include <minishell.h>

int count_pipes(t_list *tokens)
{
    t_list *aux;
    int i;

    i = 0;
    aux = tokens;
    while (aux)
    {
        if (aux->type == PIPE)
            i++;
        aux = aux->next;
    }
    return (i);
}
