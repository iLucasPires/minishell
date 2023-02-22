/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:35:38 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 16:01:59 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

// libraries local
# include "../libft/includes/libft.h"
# include "./minishell_colors.h"
# include "./minishell_define.h"
# include "./minishell_enum.h"
# include "./minishell_struct.h"
# include "./minishell_prototypes.h"
# include "./minishell_global.h"

#endif
