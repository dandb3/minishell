/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:26:26 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/12 16:10:29 by jdoh             ###   ########seoul.kr  */
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

void	*error_manage(t_node *cur_token, t_tree *root, t_list *stack)
{
	const char	*front_msg = "bash: syntax error near unexpected token `";
	const char	*back_msg = "\'\n";
	char		*token_val;

	token_val = find_token_val(cur_token);
	write(STDERR_FILENO, front_msg, ft_strlen(front_msg));
	write(STDERR_FILENO, token_val, ft_strlen(token_val));
	write(STDERR_FILENO, back_msg, ft_strlen(back_msg));
	while (!stack_empty(stack))
		pop(stack);
	free_list(stack, 0, LEX);
	free_tree(root);
	free(token_val);
	return (NULL);
}
