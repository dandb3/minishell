/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:40:00 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/11 23:02:31 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	make_token_list(t_list **token_list, t_list *env_list, char const *str)
{
	*token_list = make_list(LEX);
	while (*str)
		push_node(get_pseudo_token(&str), *token_list);
	if (pseudo_expand_env(*token_list) == FAILURE)
	{
		write(STDERR_FILENO, "MINI: syntax error: quote is not closed\n", 40);
		return (FAILURE);
	}
	del_quotes(*token_list);
	group_compound(*token_list);
	del_whitespace(*token_list);
	return (SUCCESS);
}
