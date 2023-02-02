/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:43:41 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/27 10:10:19 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "../minishell.h"
# include <stdlib.h>

typedef enum e_lex
{
	LEX_SINGLE_QUOTE,
	LEX_DOUBLE_QUOTE,
	LEX_REDIRECT_IN,
	LEX_REDIRECT_OUT,
	LEX_HERE_DOC,
	LEX_REDIRECT_APP,
	LEX_PIPE,
	LEX_ENV,
	LEX_AND,
	LEX_OR,
	LEX_WILD,
	LEX_WORD,
	LEX_WHITE,
	LEX_PARENTHESIS_OPEN,
	LEX_PARENTHESIS_CLOSE
}			t_lex;

typedef enum e_flg
{
	SYN_NO_QUOTE,
	SYN_SINGLE_QUOTE,
	SYN_DOUBLE_QUOTE,
	SYN_PARENTHESIS
}			t_flg;


long long	free_ret(void *obj1, void *obj2, void *obj3, long long ret);

/*----------------------------doubly linked list----------------------------*/
t_list		*make_list(void);
void		push_node(t_node *node, t_list *list);
void		insert_node(t_node *insert_point, t_node *node);
long long	free_nodes(t_list *list, long long ret);
long long	free_list(t_list *list, long long ret);

/*--------------------------------node list--------------------------------*/
t_list		*make_node_list(char const *str);
t_node		*make_node(char *val, t_lex lex);
void		del_node(t_node *node);
void		free_node(t_node *node);

#endif
