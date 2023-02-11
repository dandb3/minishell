#include "parser.h"

void	del_quotes(t_list *token_list)
{
	t_node	*cur_token;

	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_DOUBLE_QUOTE \
			|| cur_token->lex == LEX_SINGLE_QUOTE)
		{
			free(cur_token->val);
			cur_token->lex = LEX_WORD;
			cur_token->val = ft_strdup("");
			if (cur_token->val == NULL)
				exit(MALLOC_FAILURE);
		}
		cur_token = cur_token->next;
	}
}

int	del_whitespace(t_list *token_list)
{
	t_node *cur_token;
	int		parentheses_cnt;

	parentheses_cnt = 0;
	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_PARENTHESIS_OPEN)
			++parentheses_cnt;
		else if (cur_token->lex == LEX_PARENTHESIS_CLOSE)
			--parentheses_cnt;
		if (parentheses_cnt < 0)
			return (FAILURE);
		if (cur_token->lex == LEX_WHITE)
		{
			cur_token = cur_token->prev;
			del_node(cur_token->next,LEX);
		}
		cur_token = cur_token->next;
	}
	if (parentheses_cnt != 0)
		return (FAILURE);
	return (SUCCESS);
}
