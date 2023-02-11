/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:40:00 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/07 21:08:54 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	syntax_error(const char *str)
{
	printf("SYNTAX_ERROR: %s", str);
}

//"", '', ()에 대한 syntax analysis가 행해진다.
int	make_token_list(t_list **token_list, t_list *env_list, char const *str)
{
	*token_list = make_list(LEX);
	while (*str)
		push_node(get_pseudo_token(&str), *token_list);
	if (pseudo_expand_env(*token_list) == FAILURE)
	{
		syntax_error("Quotes are not closed\n");
		return (FAILURE);
	}
	del_quotes(*token_list);
	group_compound(*token_list);
	if (del_whitespace(*token_list) == FAILURE)
	{
		syntax_error("Parentheses are not matched\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
