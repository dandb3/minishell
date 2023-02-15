/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:06:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/15 15:49:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	close_redirect(t_redir_fds *red_info, t_symbol symbol, int new_fd)
{
	int	*val;

	if (symbol == AST_REDIRECT_IN)
		val = &(red_info->in_fd);
	else if (symbol == AST_REDIRECT_OUT)
		val = &(red_info->out_fd);
	else if (symbol == AST_REDIRECT_APPEND)
		val = &(red_info->append_fd);
	else if (symbol == AST_HERE_DOC)
		val = &(red_info->heredoc_fd);
	else
	{
		if (red_info->in_fd)
			close(red_info->in_fd);
		if (red_info->out_fd)
			close(red_info->out_fd);
		if (red_info->append_fd)
			close(red_info->append_fd);
		if (red_info->heredoc_fd)
			close(red_info->heredoc_fd);
		return (0);
	}
	close(*val);
	*val = new_fd;
	return (0);
}

int	manage_redirect(t_tree *cur, t_redir_fds *red_info)
{
	const char	*val = expand_char(cur->val);

	if (!cur)
		return (0);
	manage_redirect(cur->left_child);
	if (cur->symbol == AST_REDIRECT_IN)
		close_redirect(red_info, cur->symbol, read_file(val));
	else if (cur->symbol == AST_REDIRECT_OUT)
		close_redirect(red_info, cur->symbol, write_file(val));
	else if (cur->symbol == AST_REDIRECT_APPEND)
		close_redirect(red_info, cur->symbol, append_file(val));
	else if (cur->symbol == AST_HERE_DOC)
		close_redirect(red_info, cur->symbol, here_doc(val, FALSE));
	free(val);
	return (0);
}
