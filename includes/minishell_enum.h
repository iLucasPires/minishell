#ifndef MINISHELL_ENUM_H
#define MINISHELL_ENUM_H

enum					e_bool
{
	FALSE,
	TRUE
};

enum					e_type
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