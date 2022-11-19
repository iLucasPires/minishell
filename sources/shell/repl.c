#include <minishell.h>

// void	excute_command(t_repl *repl, t_command *command)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == CHILD_PROCESS)
// 	{
// 		if (execve(command->path, command->args, repl->envp) == EXE_FALL)
// 		{
// 			destruct_command(command);
// 			printf(ERROR_EXECVE);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	waitpid(pid, &repl->status, CHILD_PROCESS);
// }

void	read_eval_print_loop(t_repl *data)
{
	while (true)
	{
		data->line = readline(PROMPT);
		if (data->line == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			rl_clear_history();
			free(data->line);
			exit(EXIT_FAILURE);
		}
		if (*data->line != '\0')
		{
			add_history(data->line);
			printf("line: %s\n", data->line);
			// if (parse_command(data, &command) != false)
			// {
			// 	excute_command(data, &command);
			// }
		}
		free(data->line);
	}
}
