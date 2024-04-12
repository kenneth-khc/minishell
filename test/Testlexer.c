#include "unity.h"
#include "libft.h"
#include <stdio.h>

typedef struct s_Token_list	Tok_list;
typedef enum e_Token_types	Tok_types;

void	setUp(void)
{

}

void	tearDown(void)
{

}

#include "tokens.h"
#include "lexer.h"

void	test_one(void)
{
	Tok_list	list = scan("echo hello | wc -l > \"file\"");
	Tok_types	expected[] = {WORD, WORD, PIPE, WORD, WORD, GREATER, WORD};
	t_Token		*curr = list.head;
	int			i = 0;
	while (curr != NULL)
	{
		TEST_ASSERT_EQUAL_INT(expected[i], curr->type);
		curr = curr->next;
		i++;
	}
}

void	test_two(void)
{
	Tok_list	list = scan("< $(ABC) wc -l | wc -l >> $(outfile) > lol");
	Tok_types	expected[11] = {LESSER, WORD, WORD, WORD, PIPE, WORD, WORD, GREATER_GREATER, WORD, GREATER,
								WORD};
	t_Token		*curr = list.head;
	int			i = 0;

	// why doesn't this work
	// while (curr != NULL)
	// {
	// 	TEST_ASSERT_EQUAL_INT(expected[i], curr->type);
	// 	printf("Expected: %d\n", expected[i]);
	// 	printf("Current: %d\n", curr->type);
	// 	curr = curr->next;
	// 	i++;
	// }
	while (i < 11)
	{
		TEST_ASSERT_EQUAL_INT(expected[i], curr->type);
		printf("Expected: %d\n", expected[i]);
		printf("Current: %d\n", curr->type);
		if (i == 10)
			printf("Last: %s\n", curr->lexeme);
		curr = curr->next;
		i++;
	}
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_one);
	RUN_TEST(test_two);
	UNITY_END();
}
