#include <test.h>

void setUp(void)
{
}

void tearDown(void)
{
}

int main(void)
{
	UNITY_BEGIN();
	test_lexer();
	return (UNITY_END());
}