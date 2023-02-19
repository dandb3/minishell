/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:39:43 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/19 13:48:18 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	append_to_list(t_list *ori_list, t_list *expanded_list)
{
	t_node	*cur;
	char	*str;

	cur = expanded_list->tail->prev;
	while (cur->prev)
	{
		str = ft_strdup(cur->val);
		if (str == NULL)
			exit(MALLOC_FAILURE);
		push_node(make_node(str, -1), ori_list);
		cur = cur->prev;
	}
	free_list(expanded_list, 0, NAME);
}

static char	**list_to_char_twoptr(t_list *list)
{
	t_node	*cur;
	size_t	idx;
	char	**cmd;

	cmd = (char **)ft_calloc(list->size + 1, sizeof(char *));
	if (cmd == NULL)
		exit(MALLOC_FAILURE);
	cur = list->tail->prev;
	idx = -1;
	while (cur->prev)
	{
		cmd[++idx] = ft_strdup(cur->val);
		if (!cmd[idx])
			exit(MALLOC_FAILURE);
		cur = cur->prev;
	}
	return (cmd);
}

char	**compound_to_char_twoptr(t_tree *cur)
{
	t_list	*list;
	t_list	*expanded_list;

	list = make_list(NAME);
	while (cur)
	{
		expanded_list = expand_char(cur->val);
		cur = cur->right_child;
		append_to_list(list, expanded_list);
	}
	return (list_to_char_twoptr(list));
}
