/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:04:28 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/21 20:36:38 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	free_ret(void *obj1, void *obj2, void *obj3, long long ret)
{
	free(obj1);
	free(obj2);
	free(obj3);
	return (ret);
}

long long	free_twoptr(char **ptr, long long ret)
{
	char	**tmp;

	if (!ptr)
		return (ret);
	tmp = ptr;
	while (*ptr)
		free(*ptr++);
	free(tmp);
	return (ret);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == 0)
		exit(MALLOC_FAILURE);
	*result = 0;
	ft_strlcat(result, s1, s1_len + 1);
	ft_strlcat(result, s2, s1_len + s2_len + 1);
	free(s1);
	return (result);
}

void	error_msg(char *str, int status)
{
	if (write(STDERR_FILENO, str, ft_strlen(str)) == FAILURE)
		perror_msg("write", 1);
	exit(status);
}

void	perror_msg(char *str, int status)
{
	perror(str);
	exit(status);
}
