#include <readline/readline.h>
#include <stdio.h>
#include "minishell.h"
#include "new_parser/parser.h"

char *strs[] = {"", "", "", "", "", "", "", "", "", \
"COMP", "OR", "AND", "PIPE", "PARENT_OPEN", "PARENT_CLOSE", \
"REDIR_IN", "REDIR_OUT", "HERE_DOC", "REDIR_APP", "EOF", \
"EPSILON", "PARENTHESES", "COMMAND"};

void	print_tree(t_tree *root)
{
	char	*str;

	if (root == NULL)
		return ;
	printf("node : %s, ", strs[root->symbol]);
	if (root->symbol == AST_COMPOUND || root->symbol == AST_REDIRECT_APPEND \
		|| root->symbol == AST_REDIRECT_IN || root->symbol == AST_REDIRECT_OUT)
	{
		str = extract_pure_word(root->val);
		printf("val : %s\n", str);
		free(str);
	}
	else if (root->symbol == AST_HERE_DOC)
	{
		printf("val : %s\n", (char *)root->val);
	}
	else
		printf("NULL\n");
	print_tree(root->left_child);
	print_tree(root->right_child);
}

void	leaks(void)
{
	system("leaks testshell");
}

int main()
{
	char	*str;
	t_tree	*root;
	atexit(leaks);
	while (1)
	{
		str = readline("MINI$ ");
		if (str == NULL)
			exit(1);
		if (*str == '\0')
		{
			free(str);
			continue;
		}
		root = parser(str);
		print_tree(root);
		free_tree(root);
		free(str);
	}
}