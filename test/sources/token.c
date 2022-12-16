#include "../unity/test.h"

void test_add_item_end(void)
{
    t_token *head;

    head = NULL;
    add_item_end(&head, ft_strdup("ls"), WORD);
    add_item_end(&head, ft_strdup("|"), PIPE);
    add_item_end(&head, ft_strdup(">"), PLUSTHAN);
    add_item_end(&head, ft_strdup("<"), LESSTHAN);
    add_item_end(&head, ft_strdup("$dsad-l"), WORD);
    add_item_end(&head, ft_strdup(">>"), PLUSTHAN);
    add_item_end(&head, ft_strdup("test"), WORD);
    add_item_end(&head, ft_strdup("file\"    \""), WORD);
}

void test_parser_and_tokenize_all_together(void)
{
    char *str;
    t_token *token;

    token = NULL;
    str = ft_strdup("ls|><$dsad-l>>test file\"    \" ");
    parser_and_tokenize(str, &token);
    TEST_ASSERT_EQUAL_INT(WORD, token->type);
    TEST_ASSERT_EQUAL_STRING("ls", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_INT(PIPE, token->type);
    TEST_ASSERT_EQUAL_STRING("|", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_INT(REDIRECTION_OUT, token->type);
    TEST_ASSERT_EQUAL_STRING(">", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_INT(REDIRECTION_IN, token->type);
    TEST_ASSERT_EQUAL_STRING("<", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_INT(WORD, token->type);
    TEST_ASSERT_EQUAL_STRING("$dsad-l", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_INT(REDIRECTION_APPEND, token->type);
    TEST_ASSERT_EQUAL_STRING(">>", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_INT(WORD, token->type);
    TEST_ASSERT_EQUAL_STRING("test", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_INT(WORD, token->type);
    TEST_ASSERT_EQUAL_STRING("file\"    \"", next_item_list_linked(&token));

    free_list_linked(&token);
}

void test_parser_and_tokenize_all_separator(void)
{
	char *str;
	t_token *token;

	token = NULL;
	str = ft_strdup("ls |> < $dsad-l >> test file\"    \" ");
	parser_and_tokenize(str, &token);
	TEST_ASSERT_EQUAL_STRING("ls", next_item_list_linked(&token));
	TEST_ASSERT_EQUAL_STRING("|", next_item_list_linked(&token));
	TEST_ASSERT_EQUAL_STRING(">", next_item_list_linked(&token));
	TEST_ASSERT_EQUAL_STRING("<", next_item_list_linked(&token));
	TEST_ASSERT_EQUAL_STRING("$dsad-l", next_item_list_linked(&token));
	TEST_ASSERT_EQUAL_STRING(">>", next_item_list_linked(&token));
	TEST_ASSERT_EQUAL_STRING("test", next_item_list_linked(&token));
	TEST_ASSERT_EQUAL_STRING("file\"    \"", next_item_list_linked(&token));
	free_list_linked(&token);
}

void test_parser_and_tokenize_quote(void)
{
    char *str;
    t_token *token;

    token = NULL;
    str = ft_strdup("                                 echo \" \" \" ");
    parser_and_tokenize(str, &token);
    TEST_ASSERT_EQUAL_STRING("echo", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_STRING("\" \"", next_item_list_linked(&token));
    TEST_ASSERT_EQUAL_STRING("\"", next_item_list_linked(&token));
    free_list_linked(&token);
}

void test_parser_and_tokenize_one(void)
{
    char *str;
    t_token *token;

    token = NULL;
    str = ft_strdup("echo");
    parser_and_tokenize(str, &token);
    TEST_ASSERT_EQUAL_STRING("echo", next_item_list_linked(&token));
    free_list_linked(&token);
}

void run_test_token(void)
{
    RUN_TEST(test_parser_and_tokenize_one);
	RUN_TEST(test_add_item_end);
	RUN_TEST(test_parser_and_tokenize_all_together);
	RUN_TEST(test_parser_and_tokenize_all_separator);
}