/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:06:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/12 19:06:26 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"



int	manage_redirect(t_tree *tree_node)
{
	t_node	*cur;

	if (!tree_node)
		return (0);
	cur = ((t_list *)tree_node->val)->head->next;
	while (cur->next)
	{
		if (cur->lex == LEX_REDIRECT_IN)
			read_file((char *)(cur->val));
		else if (cur->lex == LEX_REDIRECT_OUT)
			write_file((char *)(cur->val));
		else if (cur->lex == LEX_REDIRECT_APPEND)
			append_file((char *)(cur->val));
		else if (cur->lex == LEX_HERE_DOC)
			(void) cur;
		cur = cur->next;
	}
	return (0);
}
