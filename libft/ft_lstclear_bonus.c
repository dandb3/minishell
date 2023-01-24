/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:14:56 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/11 18:00:21 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur_node;
	t_list	*del_node;

	if (lst == NULL || del == NULL)
		return ;
	del_node = *lst;
	cur_node = *lst;
	while (cur_node != NULL)
	{
		cur_node = cur_node->next;
		(*del)(del_node->content);
		free(del_node);
		del_node = cur_node;
	}
	*lst = NULL;
}
