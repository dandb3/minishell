#include "parser.h"

//"", '', ()에 대한 syntax analysis가 행해진다.
int	make_token_list(t_list **token_list, t_list *env_list, char const *str)
{
	*token_list = make_list(LEX);
	if (*token_list == NULL)
		return (FAILURE);
	while (*str)
		push_node(get_pseudo_token(&str), *token_list);
	if (expand_env(*token_list, env_list) == FAILURE)
	{
		syntax_error("Quotes are not closed\n");
		return (FAILURE);
	}
	expand_quotes(*token_list);
	merge_words(*token_list);
	if (del_white_tokens(*token_list) == FAILURE)
	{
		syntax_error("Parenthesis is not matched\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
