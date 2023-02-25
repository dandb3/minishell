/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:39:43 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

static void	append_to_list(t_list *ori_list, t_list *expanded_list)
{
	t_node	*cur;
	char	*str;

	cur = expanded_list->tail->prev;
	while (cur->prev)
	{
		if (cur->val == NULL)
			push_node(make_null_value_node(-1), ori_list);
		else
		{
			str = ft_strdup(cur->val);
			if (str == NULL)
				exit(MALLOC_FAILURE);
			push_node(make_node(str, -1), ori_list);
		}
		cur = cur->prev;
	}
}

static int	get_non_nullvalue_list_size(t_list *list)
{
	t_node	*cur;
	int		size;

	if (list == NULL)
		return (0);
	cur = list->head->next;
	size = 0;
	while (cur->next)
	{
		if (cur->val)
			++size;
		cur = cur->next;
	}
	return (size);
}

static char	**list_to_char_twoptr(t_list *list)
{
	t_node	*cur;
	char	**cmd;
	int		size;

	size = get_non_nullvalue_list_size(list);
	cmd = (char **)ft_calloc(size + 1, sizeof(char *));
	if (cmd == NULL)
		exit(MALLOC_FAILURE);
	cur = list->head->next;
	while (cur->next)
	{
		if (cur->val)
		{
			cmd[--size] = ft_strdup(cur->val);
			if (!cmd[size])
				exit(MALLOC_FAILURE);
		}
		cur = cur->next;
	}
	return (cmd);
}

char	**compound_to_char_twoptr(t_tree *cur)
{
	t_list	*list;
	t_list	*expanded_list;
	char	**cmd;

	list = make_list(NAME);
	while (cur)
	{
		expanded_list = expand_char(cur->val);
		cur = cur->right_child;
		append_to_list(list, expanded_list);
		free_list(expanded_list, 0, NAME);
	}
	cmd = list_to_char_twoptr(list);
	free_list(list, 0, NAME);
	return (cmd);
}
