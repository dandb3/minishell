/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:39:43 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/11 19:40:06 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	**compound_to_char_twoptr(t_list *list)
{
	t_node		*cur;
	char		**cmd;
	int			idx;
	const int	list_length = get_list_length(list);

	cmd = (char **)ft_calloc(list_length + 1, sizeof(char *));
	if (!cmd)
		exit(MALLOC_FAILURE);
	idx = -1;
	cur = list->head->next;
	while (++idx < list_length)
	{
		cmd[idx] = ft_strdup((char *)(cur->val));
		if (!cmd[idx])
			exit(MALLOC_FAILURE);
		cur = cur->next;
	}
	return (cmd);
}
