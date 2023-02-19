/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:26:26 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/19 20:33:05 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*find_token_val(t_node *cur_token)
{
	char	*result;

	if (cur_token->lex != LEX_COMPOUND)
	{
		result = ft_strdup(cur_token->val);
		if (result == NULL)
			exit(MALLOC_FAILURE);
		return (result);
	}
	return (extract_pure_word(cur_token->val));
}

int	error_manage(t_node *cur_token, t_list *stack)
{
	const char	*front_msg = "MINI: syntax error near unexpected token `";
	const char	*back_msg = "\'\n";
	char		*token_val;

	if (cur_token->next == NULL)
	{
		token_val = ft_strdup("newline");
		if (token_val == NULL)
			exit(MALLOC_FAILURE);
	}
	else
		token_val = find_token_val(cur_token);
	print_err(front_msg, token_val, back_msg);
	set_exitcode(258, 0);
	free_list(stack, 0, LEX);
	free(token_val);
	return (FAILURE);
}
