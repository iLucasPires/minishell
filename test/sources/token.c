#include "../unity/test.h"

void test_finite_state_machine_with_string_in_double_quotes(void)
{
	t_token *head = NULL;
	char *input = "This is a \"string in double quotes\"";
	finite_state_machine(input, &head);

	TEST_ASSERT_EQUAL_STRING("This", head->value);
	TEST_ASSERT_EQUAL_STRING("is", head->next->value);
	TEST_ASSERT_EQUAL_STRING("a", head->next->next->value);
	TEST_ASSERT_EQUAL_STRING("string in double quotes", head->next->next->next->value);
	TEST_ASSERT_NULL(head->next->next->next->next);
}

void test_finite_state_machine_with_string_in_single_quotes(void)
{
	t_token *head = NULL;
	char *input = "This is a 'string in single quotes'";
	finite_state_machine(input, &head);

	TEST_ASSERT_EQUAL_STRING("This", head->value);
	TEST_ASSERT_EQUAL_STRING("is", head->next->value);
	TEST_ASSERT_EQUAL_STRING("a", head->next->next->value);
	TEST_ASSERT_EQUAL_STRING("string in single quotes", head->next->next->next->value);
	TEST_ASSERT_NULL(head->next->next->next->next);
}

void test_finite_state_machine_with_redirection_in(void)
{
	t_token *head = NULL;
	char *input = "This is a < redirect";
	finite_state_machine(input, &head);

	TEST_ASSERT_EQUAL_STRING("This", head->value);
	TEST_ASSERT_EQUAL_STRING("is", head->next->value);
	TEST_ASSERT_EQUAL_STRING("a", head->next->next->value);
	TEST_ASSERT_EQUAL_STRING("<", head->next->next->next->value);
	TEST_ASSERT_EQUAL_STRING("redirect", head->next->next->next->next->value);
	TEST_ASSERT_NULL(head->next->next->next->next->next);
}

void test_finite_state_machine_with_complex_input(void)
{
	t_token *head = NULL;
	char *input = "This is a 'string in single quotes' with < redirection in and > redirection out, plus some \"mixed quotes\" and a | pipe";
	finite_state_machine(input, &head);

	TEST_ASSERT_EQUAL_STRING("This", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("is", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("a", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("string in single quotes", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("with", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("<", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("redirection", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("in", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("and", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING(">", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("redirection", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("out", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("plus", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("some", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("mixed quotes", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("and", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("a", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("|", next_item_list_linked(&head));
	TEST_ASSERT_EQUAL_STRING("pipe", next_item_list_linked(&head));
    TEST_ASSERT_NULL(head);
}




void run_test_token(void)
{
    RUN_TEST(test_finite_state_machine_with_string_in_double_quotes);
    RUN_TEST(test_finite_state_machine_with_string_in_single_quotes);
    RUN_TEST(test_finite_state_machine_with_redirection_in);
    RUN_TEST(test_finite_state_machine_with_complex_input);
}