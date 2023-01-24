/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:21:22 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/14 13:24:36 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*make_node(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*new_content;
	t_list	*new_node;

	new_content = (*f)(lst->content);
	if (new_content == NULL)
		return (NULL);
	new_node = ft_lstnew(new_content);
	if (new_node == NULL)
	{
		(*del)(new_content);
		return (NULL);
	}
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;
	t_list	*cur_node;

	if (f == 0 || del == 0 || lst == 0)
		return (NULL);
	new_list = make_node(lst, f, del);
	if (new_list == NULL)
		return (NULL);
	lst = lst->next;
	cur_node = new_list;
	while (lst != NULL)
	{
		new_node = make_node(lst, f, del);
		if (new_node == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		cur_node->next = new_node;
		cur_node = cur_node->next;
		lst = lst->next;
	}
	return (new_list);
}
