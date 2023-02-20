/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:56:32 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/20 19:26:02 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	set_heredoc_status(1);
	set_exitcode(128 + sig, 0);
}

void	set_heredoc_status(int status)
{
	heredoc_status(status);
}

int	get_heredoc_status(void)
{
	return (heredoc_status(2));
}
