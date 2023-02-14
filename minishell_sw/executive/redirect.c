/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:06:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/13 19:02:27 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	manage_redirect(t_tree *tree_node)
{
	t_tree	*cur;

	if (!tree_node)
		return (0);
	cur = tree_node;
	while (cur)
	{
		if (cur->symbol == LEX_REDIRECT_IN)
			read_file((char *)(cur->val));
		else if (cur->symbol == AST_REDIRECT_OUT)
			write_file((char *)(cur->val));
		else if (cur->symbol == AST_REDIRECT_APP)
			append_file((char *)(cur->val));
		else if (cur->symbol == AST_HERE_DOC)
			here_doc((char *)(cur->val), FALSE);
	}
	return (0);
}
