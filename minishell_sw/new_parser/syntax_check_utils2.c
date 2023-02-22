/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:56:32 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/21 20:58:23 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	syntax_init(t_node **cur_token, t_list **stack, t_list *token_list)
{
	set_heredoc_status(0);
	*cur_token = token_list->head->next;
	*stack = make_list(LEX);
	push(*stack, make_tree(AST_E0));
}

static int	heredoc_status(int mode)
{
	static int	status;

	if (mode == 0)
		status = 0;
	else if (mode == 1)
		status = 1;
	else
		return (status);
	return (SUCCESS);
}

void	heredoc_handler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	set_heredoc_status(1);
	set_exitcode(1, 0);
}

void	set_heredoc_status(int status)
{
	heredoc_status(status);
}

int	get_heredoc_status(void)
{
	return (heredoc_status(2));
}
