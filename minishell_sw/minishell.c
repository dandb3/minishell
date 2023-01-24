/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:36:29 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/24 11:17:58 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks a.out");
}

int	main(int ac, char **av)
{
	char	*buf;
	size_t	size;
	char	*str;

	str = NULL;
	size = 100;
	(void) ac;
	(void) av;
	(void) str;
	(void) buf;
	str = getcwd(NULL, 150);
	printf("%s\n", str);
	free(str);
	return (0);
}
