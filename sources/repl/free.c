#include <minishell.h>

void free_minishell(t_repl *data)
{
    rl_clear_history();
    free_list_linked(&data->env);
    free_list_linked(&data->head);
    free(data->path);
    free(data->line);
}

void free_repl(t_repl *data)
{
    free(data->line);
    free_list_linked(&data->head);
}

void free_exit_minishell(t_repl *data, int status)
{
    free_minishell(data);
    exit(status);
}
