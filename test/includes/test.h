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

/*
Functions to be tested
*/

void test_lexer(void);
void test_check_line(void);
void token(void);
char **lexer(char *line);

#endif