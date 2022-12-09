#include "test.h"

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
	RUN_TEST(test_make_token);
	return (UNITY_END());
}
