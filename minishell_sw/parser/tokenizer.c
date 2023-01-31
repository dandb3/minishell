/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodeizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:15:52 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/27 09:55:36 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*find_env(char *str, char *envp[])
{
	size_t	len;

	len = ft_strlen(str);
	while (*envp)
	{
		if (!ft_strncmp(str, *envp, len) && (*envp)[len] == '=')
			return (ft_substr(*envp, len + 1, ft_strlen(*envp)));
		envp++;
	}
	return (ft_strdup(""));
}

t_list	*tokenizer(char const *str, char *envp[])
{
	t_list	*result;

	result = make_node_list(str);
	if (result == NULL)
		return (NULL);
	expand_env(result, envp);
	delete_quotes(result);
	merge_and_delete(result);
}

// void	expand_env(t_list *result, char *envp[])
// {
// 	t_node	*cur;
// 	t_flg	flag;

// 	flag = SYN_NO_QUOTE;
// 	cur = result->head->next;
// 	while (cur->next != NULL)
// 	{
// 		if (flag == SYN_NO_QUOTE)
// 		{
// 			if (cur->lex == SYN_SINGLE_QUOTE)
// 				flag = SYN_
			
// 		if (flag == SYN_NO_QUOTE || flag == SYN_DOUBLE_QUOTE)
// 		{
			
// 		}
// 	}
// }
