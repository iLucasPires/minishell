/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsmachine_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:38:59 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 14:38:59 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fsm_is_state(char *str, int index)
{
	if (str[index] == PLUSTHAN)
	{
		if (str[index + 1] == PLUSTHAN)
			return (RED_APPEND);
		return (RED_OUT);
	}
	else if (str[index] == LESSTHAN)
	{
		if (str[index + 1] == LESSTHAN)
			return (HEREDOC);
		return (RED_IN);
	}
	else if (str[index] == BAR)
		return (PIPE);
	else
		return (FALSE);
}

int	fsm_is_space(char *str, int index)
{
	if (str[index] == SPACE || str[index] == NULL_CHAR)
		return (TRUE);
	return (FALSE);
}

int	fsm_is_special(char *str, int index)
{
	if (fsm_is_state(str, index) || fsm_is_space(str, index))
		return (TRUE);
	return (FALSE);
}

char	*fsm_identified(int identifier)
{
	if (identifier == RED_IN)
		return ("<");
	if (identifier == RED_OUT)
		return (">");
	if (identifier == PIPE)
		return ("|");
	if (identifier == RED_APPEND)
		return (">>");
	if (identifier == HEREDOC)
		return ("<<");
	return ("");
}

pid_t	ft_getpid(void)
{
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;
	char	*current_line;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == FAILURE)
		return ((pid_t)FAILURE);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read == FAILURE)
		return ((pid_t)FAILURE);
	buffer[bytes_read] = '\0';
	current_line = ft_strnstr(buffer, "Pid:", bytes_read);
	if (current_line == NULL)
		return ((pid_t)FAILURE);
	return (ft_atoi(current_line + 4));
}
