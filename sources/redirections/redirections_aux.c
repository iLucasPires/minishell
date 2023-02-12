#include <minishell.h>

int	open_file(char *file, int flags, int other_flags, u_int8_t *exit_code)
{
	int	fd;
	int	is_file;

	if (other_flags == 0)
	{
		is_file = access(file, F_OK);
		if (is_file == -1)
		{
			perror("minishell");
			*exit_code = 1;
			return (FAILURE);
		}
		fd = open(file, flags);
	}
	else
		fd = open(file, flags, other_flags);
	if (fd == FAILURE)
	{
		perror("open");
		*exit_code = 1;
		return (FAILURE);
	}
	return (fd);
}

int	is_redirect(int identifier)
{
	return (identifier == RED_IN || identifier == RED_OUT ||
			identifier == RED_APPEND || identifier == HEREDOC);
}
