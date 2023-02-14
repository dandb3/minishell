/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:12:46 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/14 14:09:12 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*make_ast(t_list *token_list)
{
	t_tree	*root;
	t_node	*cur_token;
	char	*val;

	val = ft_strdup("");
	if (val == NULL)
		exit(MALLOC_FAILURE);
	push_node(make_node(val, LEX_PARENTHESIS_CLOSE), token_list);
	cur_token = token_list->head->next;
	return (make_expression(&cur_token));
}
