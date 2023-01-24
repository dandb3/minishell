/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:43:41 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/24 18:52:48 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdlib.h>

typedef enum e_status
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
	LEX_WHITE
}			t_status;

typedef enum e_flg
{
	SYN_NO_QUOTE,
	SYN_SINGLE_QUOTE,
	SYN_DOUBLE_QUOTE
}			t_flg;

typedef struct s_token
{
	char			*val;
	struct s_token	*next;
	struct s_token	*prev;
	t_status		status;
}				t_token;

typedef struct s_lst
{
	struct s_token	*head;
	struct s_token	*tail;
	int				size;
}				t_lst;

long long	free_ret(void *obj1, void *obj2, void *obj3, long long ret);

/*----------------------------doubly linked list----------------------------*/
t_lst		*make_list(void);
void		push_token(t_token *token, t_lst *list);
long long	free_tokens(t_lst *list, long long ret);
long long	free_list(t_lst *list, long long ret);

/*--------------------------------token list--------------------------------*/
t_lst		*make_token_list(char const *str);
t_token		*make_token(char *val, t_status status);
void		del_token(t_token *token);
void		free_token(t_token *token);

#endif
