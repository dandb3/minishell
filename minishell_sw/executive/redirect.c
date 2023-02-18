/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:06:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 20:28:09 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	manage_redirect(t_tree *cur)
{
	char	*val;
	int		status;

	status = 0;
	if (!cur)
		return (SUCCESS);
	if (manage_redirect(cur->left_child) == 1)
		return (1);
	if (cur->symbol == AST_HERE_DOC)
	{
		val = cur->val;
		cur->val = NULL;
	}
	else
		val = expand_char(cur->val);
	if (cur->symbol == AST_REDIRECT_IN)
		status = read_file(val);
	else if (cur->symbol == AST_REDIRECT_OUT)
		status = write_file(val);
	else if (cur->symbol == AST_REDIRECT_APPEND)
		status = append_file(val);
	else if (cur->symbol == AST_HERE_DOC)
		status = here_doc(val, FALSE);
	free(val);
	return (status);
}
