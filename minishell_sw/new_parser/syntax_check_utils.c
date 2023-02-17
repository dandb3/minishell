/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:03:28 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/17 09:37:17 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static char	*read_here_doc(char *here_doc_end)
{
	char	*total_line;
	char	*cur_line;

	total_line = ft_strdup("");
	if (total_line == NULL)
		exit(MALLOC_FAILURE);
	cur_line = readline("> ");
	while (cur_line != NULL && ft_strcmp(here_doc_end, cur_line))
	{
		total_line = ft_strjoin_and_free(total_line, cur_line);
		total_line = ft_strjoin_and_free(total_line, "\n");
		free(cur_line);
		cur_line = readline("> ");
	}
	free(cur_line);
	return (total_line);
}

void	here_doc_or_pop(t_list *stack, t_node **cur_token, t_symbol symbol)
{
	char	*here_doc_end;

	if ((*cur_token)->lex == LEX_COMPOUND && (*cur_token)->prev->lex == LEX_HERE_DOC)
	{
		del_quotes((*cur_token)->val);
		here_doc_end = extract_pure_word((*cur_token)->val);
		free_list((*cur_token)->val, 0, LEX);
		(*cur_token)->val = read_here_doc(here_doc_end);
		free(here_doc_end);
	}
	*cur_token = (*cur_token)->next;
	pop_tree(stack);
}
