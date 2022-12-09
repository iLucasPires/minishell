#ifndef TEST_H
#define TEST_H

#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../../includes/minishell.h"

#define DQUOTE '\"'
#define SQUOTE '\''
#define BSLASH '\\'
#define PLUSTHAN '>'
#define LESSTHAN '<'

/*
Functions to be tested
*/

typedef struct s_token
{
    char *value;
    int type;
    struct s_token *next;
} t_token;

enum e_type
{
    REDIRECTION,
    WORD,
    COUPLE_REDIRECTION,
};


void test_lexer(void);
void test_check_line(void);
void token(void);
char **lexer(char *line);
void test_make_token(void);


#endif