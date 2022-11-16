#include <minishell.h>

void	init_repl(t_repl *repl)
{
	while (true)
	{
		repl->line = readline(PROMPT);
		if (repl->line == NULL)
			break ;
		add_history(repl->line);
		free(repl->line);
	}
}