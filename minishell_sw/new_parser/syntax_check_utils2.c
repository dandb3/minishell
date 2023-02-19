/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:56:32 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/19 21:13:27 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

void	init_heredoc_status(void)
{
	heredoc_status(0);
}

void	set_heredoc_status(void)
{
	heredoc_status(1);
}

int	get_heredoc_status(void)
{
	return (heredoc_status(2));
}
