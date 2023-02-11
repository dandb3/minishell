/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:43:28 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/09 13:40:09 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "../minishell.h"

typedef enum e_parse
{
	PARSE_AND = 0,
	PARSE_OR,
	PARSE_PIPE,
	PARSE_PAREN,
	PARSE_REDIR,
	PARSE_EXEC
}	t_parse;

typedef struct s_element
{
	struct s_element	*left;
	struct s_element	*right;
	void				*val;
	t_parse				ptype;
}	t_element;

#endif