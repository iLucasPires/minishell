#include <minishell.h>

void	path_current(t_repl *data)
{
	char	*path;
	char	*temp;

	path = getcwd(NULL, 0);
	if (ft_strncmp(path, getenv("HOME"), ft_strlen(path)))
		data->path = ft_strjoin(BHGREEN"~", path + ft_strlen(getenv("HOME")));
	else
		data->path = ft_strjoin(BHGREEN, path);
	temp = data->path;
	data->path = ft_strjoin(data->path, BHGREEN" $ " RESET);
	free(temp);
	free(path);
}
