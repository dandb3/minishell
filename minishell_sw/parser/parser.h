/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:43:41 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/03 19:06:48 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

typedef enum s_flag
{
	UN_QUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED
}		t_flag;

/*---------------------------------tokenize---------------------------------*/
t_node	*get_pseudo_token(char const **str);
int		expand_env(t_list *token_list, t_list *env_list);
void	expand_quotes(t_list *token_list);
void	merge_words(t_list *token_list);
void	merge_two_words(t_node *w1, t_node *w2);
int		del_white_tokens(t_list *token_list);

#endif
