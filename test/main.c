#include "./unity/test.h"

void setUp(void)
{
}

void tearDown(void)
{
}

int main(void)
{
	UNITY_BEGIN();
	// test_lexer();
  
  // test_check_line();
	RUN_TEST(run_test_list);
	// RUN_TEST(test_expander);
	return (UNITY_END());
}
