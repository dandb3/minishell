/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:03:28 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/12 16:08:31 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "parser.h"

static void	env_to_word(t_node *env_token)
{
	char	*tmp;

	env_token->lex = LEX_WORD;
	tmp = ft_strjoin("$", env_token->val);
	free(env_token->val);
	env_token->val = tmp;
}

static void	merge_two_words(t_node *prev_token, t_node *cur_token)
{
	char	*merged_word;

	merged_word = ft_strjoin(prev_token->val, cur_token->val);
	if (merged_word == NULL)
		exit(MALLOC_FAILURE);
	free(cur_token->val);
	cur_token->val = merged_word;
	del_node(prev_token, LEX);
}

char	*extract_pure_word(t_list *compound_list)
{
	t_node	*cur_token;
	char	*ret;

	cur_token = compound_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_ENV)
			env_to_word(cur_token);
		if (cur_token->prev->lex != -1)
			merge_two_words(cur_token->prev, cur_token);
		cur_token = cur_token->next;
	}
	ret = compound_list->head->next->val;
	compound_list->head->next->val = NULL;
	return (ret);
}

static char	*read_here_doc(char *here_doc_end)
{
	char	*total_line;
	char	*cur_line;

	total_line = ft_strdup("");
	if (total_line == NULL)
		exit(MALLOC_FAILURE);
	cur_line = readline("< ");
	while (cur_line != NULL && ft_strcmp(here_doc_end, cur_line))
	{
		total_line = ft_strjoin_and_free(total_line, cur_line);
		total_line = ft_strjoin_and_free(total_line, "\n");
		free(cur_line);
		cur_line = readline("< ");
	}
	free(cur_line);
	return (total_line);
}

void	insert_and_pop(t_list *stack, t_tree *cur_tree, t_node *cur_token)
{
	char	*here_doc_end;

	if (cur_token->lex == LEX_COMPOUND)
	{
		cur_tree->val = copy_list(cur_token->val);
		if (cur_token->prev->lex == LEX_HERE_DOC)
		{
			del_quotes(cur_tree->val);
			here_doc_end = extract_pure_word(cur_tree->val);
			free_list(cur_tree->val, 0, LEX);
			cur_tree->val = read_here_doc(here_doc_end);
			free(here_doc_end);
		}
	}
	pop(stack);
}
