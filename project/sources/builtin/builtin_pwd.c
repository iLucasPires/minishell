/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:37:54 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 15:54:14 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_pwd(char **args, t_minishell *data)
{
	char	*path;

	(void)args;
	path = getcwd(NULL, 0);
	if (path == NULL || path[0] == '\0')
	{
		perror("getcwd");
		data->exit_code = 1;
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}
