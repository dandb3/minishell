/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:26:26 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/11 19:27:04 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*error_manage(t_node *cur_token, t_tree *root, t_list *stack)
{
	while (!stack_empty(stack))
		pop(stack);
	free_tree(root);
	return (NULL);
}
