/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_nodeizer2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:56:05 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/27 09:56:07 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*get_node(char const **str);

t_list	*make_node_list(char const *str)
{
	t_list		*result;
	t_node		*new_node;

	result = make_list();
	if (result == NULL)
		return (NULL);
	while (*str)
	{
		new_node = get_node(&str);
		if (new_node == NULL)
			return ((t_list *)free_list(result, 0));
		push_node(new_node, result);
	}
	return (result);
}
