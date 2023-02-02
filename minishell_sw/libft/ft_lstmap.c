/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:30:27 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/18 11:06:52 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lstset(void *content, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	void	*tmp_content;

	tmp_content = f(content);
	if (tmp_content == 0)
		return (0);
	tmp = ft_listnew(tmp_content);
	if (tmp == 0)
		del(tmp_content);
	return (tmp);
}

t_list	*ft_listmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tail;
	t_list	*head;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	tmp = lstset(lst->content, f, del);
	if (tmp == 0)
		return (0);
	head = tmp;
	tail = tmp;
	lst = lst->next;
	while (lst)
	{
		tmp = lstset(lst->content, f, del);
		if (tmp == 0)
		{
			ft_listclear(&head, del);
			return (0);
		}
		tail->next = tmp;
		tail = tail->next;
		lst = lst->next;
	}
	return (head);
}
