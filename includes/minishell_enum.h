/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enum.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n < lpires-n@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:50 by lpires-n          #+#    #+#             */
/*   Updated: 2023/02/13 14:36:53 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENUM_H
# define MINISHELL_ENUM_H

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_type
{
	WORD,
	RED_IN,
	RED_OUT,
	RED_APPEND,
	HEREDOC,
	PIPE,
	QUOTE,
	DOCUMENT,
};

#endif