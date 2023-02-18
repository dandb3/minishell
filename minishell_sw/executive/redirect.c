/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:06:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/17 20:33:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	manage_redirect(t_tree *cur)
{
	char	*val;

	if (!cur)
		return ;
	if (cur->symbol == AST_HERE_DOC)
	{
		val = cur->val;
		cur->val = NULL;
	}
	else
		val = expand_char(cur->val);
	manage_redirect(cur->left_child);
	if (cur->symbol == AST_REDIRECT_IN)
		read_file(val);
	else if (cur->symbol == AST_REDIRECT_OUT)
		write_file(val);
	else if (cur->symbol == AST_REDIRECT_APPEND)
		append_file(val);
	else if (cur->symbol == AST_HERE_DOC)
		here_doc(val, FALSE);
	free(val);
}
