/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:15:26 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/24 16:06:49 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*make_token(char *val, t_status status)
{
	t_token	*result;

	if (val == NULL)
		return (NULL);
	result = (t_token *) malloc(sizeof(t_token));
	if (result == NULL)
		return ((t_token *)free_ret(val, NULL, NULL, 0));
	ft_memset(result, 0, sizeof(t_token));
	result->val = val;
	result->status = status;
	return (result);
}

void	free_token(t_token *token)
{
	free(token->val);
	free(token);
}
