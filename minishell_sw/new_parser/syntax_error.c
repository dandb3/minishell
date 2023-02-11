/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:26:26 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/11 23:02:49 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*error_manage(t_node *cur_token, t_tree *root, t_list *stack)
{
	const char	*front_msg = "bash: syntax error near unexpected token `";
	const char	*back_msg = "\'\n";

	write(STDERR_FILENO, front_msg, ft_strlen(front_msg));
	
	write(STDERR_FILENO, back_msg, ft_strlen(back_msg));
	while (!stack_empty(stack))
		pop(stack);
	free_tree(root);
	return (NULL);
}
