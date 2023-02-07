#include <minishell.h>

void	dup_fds(t_command *cmd)
{
	if (cmd->infile > 2)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile > 2)
		dup2(cmd->outfile, STDOUT_FILENO);
}

// void	dup_saved_fds(int saved[2])
// {
// 	dup2(saved[STDIN_FILENO], STDIN_FILENO);
// 	dup2(saved[STDOUT_FILENO], STDOUT_FILENO);
// }

void	close_fds(t_command *cmd)
{
	// int			i;

	// i = 3;
	// while (!close(i))
	// {
	// 	i++;
	// }
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
}

// void	close_saved_fds(int saved[2])
// {
// 	close(saved[STDIN_FILENO]);
// 	close(saved[STDOUT_FILENO]);
// }