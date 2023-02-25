/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:30:20 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

static void	pop_push2(t_list *stack, t_symbol s1, t_symbol s2)
{
	pop_tree(stack);
	if (s2 != -1)
		push(stack, make_tree(s2));
	if (s1 != -1)
		push(stack, make_tree(s1));
}

static void	production_exception(t_list *stack,	t_table table_result)
{
	if (table_result == E8_REDIRECT_IN)
		pop_push2(stack, AST_REDIRECT_IN, AST_COMPOUND);
	else if (table_result == E8_REDIRECT_OUT)
		pop_push2(stack, AST_REDIRECT_OUT, AST_COMPOUND);
	else if (table_result == E8_REDIRECT_APPEND)
		pop_push2(stack, AST_REDIRECT_APPEND, AST_COMPOUND);
	else if (table_result == E8_HERE_DOC)
		pop_push2(stack, AST_HERE_DOC, AST_COMPOUND);
	else if (table_result == E5_PARENTHESES)
	{
		pop_tree(stack);
		push(stack, make_tree(AST_E4));
		push(stack, make_tree(AST_PARENTHESES_CLOSE));
		push(stack, make_tree(AST_E0));
		push(stack, make_tree(AST_PARENTHESES_OPEN));
	}
}

void	production(t_list *stack, t_table table_result)
{
	if (table_result == E0_E2_E1)
		pop_push2(stack, AST_E2, AST_E1);
	else if (table_result == E1_OR_E0)
		pop_push2(stack, AST_OR, AST_E0);
	else if (table_result == E1_AND_E0)
		pop_push2(stack, AST_AND, AST_E0);
	else if (table_result == E1_EPSILON || table_result == E3_EPSILON \
		|| table_result == E4_EPSILON || table_result == E6_EPSILON)
		pop_push2(stack, AST_EPSILON, -1);
	else if (table_result == E2_E5_E3)
		pop_push2(stack, AST_E5, AST_E3);
	else if (table_result == E3_PIPE_E2)
		pop_push2(stack, AST_PIPE, AST_E2);
	else if (table_result == E4_E8_E4)
		pop_push2(stack, AST_E8, AST_E4);
	else if (table_result == E5_E7_E6 || table_result == E6_E7_E6)
		pop_push2(stack, AST_E7, AST_E6);
	else if (table_result == E7_COMP)
		pop_push2(stack, AST_COMPOUND, -1);
	else if (table_result == E7_E8)
		pop_push2(stack, AST_E8, -1);
	else
		production_exception(stack, table_result);
}
