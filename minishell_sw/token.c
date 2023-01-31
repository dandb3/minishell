/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:15:26 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/25 16:34:59 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*make_node(void *val, t_lex lex)
{
	t_node	*result;

	if (val == NULL)
		return (NULL);
	result = (t_node *) malloc(sizeof(t_node));
	if (result == NULL)
		exit(MALLOC_FAILURE);
	ft_memset(result, 0, sizeof(t_node));
	result->val = val;
	result->lex = lex;
	return (result);
}

void	free_node(t_node *node, t_type type)
{
	if (type == ENV)
	{
		free(((t_env *)(node->val))->val);
		free(((t_env *)(node->val))->key);
	}
	free(node->val);
	free(node);
}
