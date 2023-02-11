#include "parser.h"

static void	make_parsing_table(char **table)
{
	table[AST_E0] = "\1\0\0\0\1\0\1\1\1\1\0";
	table[AST_E1] = "\0\2\3\0\0\4\0\0\0\0\4";
	table[AST_E2] = "\5\0\0\0\5\0\5\5\5\5\0";
	table[AST_E3] = "\0\7\7\6\0\7\0\0\0\0\7";
	table[AST_E4] = "\0\11\11\11\0\11\10\10\10\10\11";
	table[AST_E5] = "\13\0\0\0\12\0\13\13\13\13\0";
	table[AST_E6] = "\14\15\15\15\0\15\14\14\14\14\15";
	table[AST_E7] = "\16\0\0\0\0\0\17\17\17\17\0";
	table[AST_E8] = "\0\0\0\0\0\0\20\21\22\23\0";
}

static void	pop_push2(t_list *stack, t_tree *cur_tree, t_symbol s1, t_symbol s2)
{
	t_tree	*left_child;
	t_tree	*right_child;

	pop(stack);
	left_child = make_tree(s1);
	cur_tree->left_child = left_child;
	push(stack, left_child);
	if (s2 < 0)
		return ;
	right_child = make_tree(s2);
	cur_tree->right_child = right_child;
	push(stack, right_child);
}

static void	production_exception(t_list *stack, t_tree *cur_tree, t_table table_result)
{
	if (table_result == E8_REDIRECT_IN)
		pop_push2(stack, cur_tree, AST_REDIRECT_IN, AST_COMPOUND);
	if (table_result == E8_REDIRECT_OUT)
		pop_push2(stack, cur_tree, AST_REDIRECT_OUT, AST_COMPOUND);
	if (table_result == E8_REDIRECT_APPEND)
		pop_push2(stack, cur_tree, AST_REDIRECT_APPEND, AST_COMPOUND);
	if (table_result == E8_HERE_DOC)
	{
		pop_push2(stack, cur_tree, AST_HERE_DOC, AST_COMPOUND);
		//히어독 입력받기;
	}
	if (table_result == E5_PARENTHESES)
	{
		//괄호 예외처리;
	}
}

static void	production(t_list *stack, t_tree *cur_tree, t_table table_result)
{
	if (table_result == E0_E2_E1)
		pop_push2(stack, cur_tree, AST_E2, AST_E1);
	if (table_result == E1_OR_E0)
		pop_push2(stack, cur_tree, AST_OR, AST_E0);
	if (table_result == E1_AND_E0)
		pop_push2(stack, cur_tree, AST_AND, AST_E0);
	if (table_result == E1_EPSILON || table_result == E3_EPSILON \
		|| table_result == E4_EPSILON || table_result == E6_EPSILON)
		pop_push2(stack, cur_tree, AST_EPSILON, -1);
	if (table_result == E2_E5_E3)
		pop_push2(stack, cur_tree, AST_E5, AST_E3);
	if (table_result == E3_PIPE_E2)
		pop_push2(stack, cur_tree, AST_PIPE, AST_E2);
	if (table_result == E4_E8_E4)
		pop_push2(stack, cur_tree, AST_E8, AST_E4);
	if (table_result == E5_E7_E6 || table_result == E6_E7_E6)
		pop_push2(stack, cur_tree, AST_E7, AST_E6);
	if (table_result == E7_COMP_E8)
		pop_push2(stack, cur_tree, AST_COMPOUND, AST_E8);
	else
		production_exception(stack, cur_tree, table_result);
}

t_tree	*make_parse_tree(t_list *token_list)
{
	char	*table[9];
	t_list	*stack;
	t_tree	*root;
	t_node	*cur_token;
	t_tree	*cur_tree;

	cur_token = token_list->head->next;
	make_parsing_table(table);
	stack = make_list(NAME);
	root = make_tree(AST_E0);
	push(stack, root);
	while (!stack_empty(stack))
	{
		cur_tree = top(stack)->val;
		if (cur_tree->symbol == cur_token->lex + 4)
		{
			pop(stack);
			cur_token = cur_token->next;
		}
		else if (cur_tree->symbol >= AST_COMPOUND)
			ERROR;
		else if (table[cur_tree->symbol][cur_token->lex - 6] == SYNTAX_ERROR)
			ERROR;
		else if (table[cur_tree->symbol][cur_token->lex - 6] == E5_PARENTHESES)
			production_parentheses(stack, table, );
		else
			production(stack, table[cur_tree->symbol][cur_token->lex - 6],
				cur_tree);
	}
	if (cur_token->next != NULL)
		ERROR;
}