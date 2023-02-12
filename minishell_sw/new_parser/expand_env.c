#include "parser.h"

static void	substitute_env(t_node *compound_token)
{
	t_node	*cur_token;
	char	*env_val;

	cur_token = ((t_list *)(compound_token->val))->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_ENV)
		{
			env_val = find_env_val(g_env_list, cur_token->val);
			free(cur_token->val);
			cur_token->val = env_val;
			if (cur_token->val == NULL)
			{
				cur_token = cur_token->prev;
				del_node(cur_token->next, LEX);
			}
			else
				cur_token->lex = LEX_WORD;
		}
		cur_token = cur_token->next;
	}
}

static void	merge_two_words(t_node *prev_token, t_node *cur_token)
{
	char	*merged_word;

	if (prev_token->lex == LEX_WILD || cur_token->lex == LEX_WILD)
		cur_token->lex = LEX_WILD;
	merged_word = ft_strjoin(prev_token->val, cur_token->val);
	if (merged_word == NULL)
		exit(MALLOC_FAILURE);
	free(cur_token->val);
	cur_token->val = merged_word;
	del_node(prev_token, LEX);
}

static void	merge_words(t_node *compound_token)
{
	t_node	*cur_token;

	cur_token = ((t_list *)(compound_token->val))->head->next;
	while (cur_token->next != NULL)
	{
		if ((cur_token->lex == LEX_WORD || cur_token->lex == LEX_WILD) \
			&& (cur_token->prev->lex == LEX_WORD \
				|| cur_token->prev->lex == LEX_WILD))
			merge_two_words(cur_token->prev, cur_token);
		cur_token = cur_token->next;
	}
}

static void	compound_to_word(t_node *compound_token)
{
	substitute_env(g_env_list, compound_token);
	merge_words(compound_token);
	exchange_token(cur_token);
}
