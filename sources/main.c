#include <minishell.h>

int main(void)
{
    t_data data;

    init_repl(&data.repl);
    printf("Hello World!");

    return 0;
}