# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 19:25:02 by jdoh              #+#    #+#              #
#    Updated: 2023/02/25 13:25:17 by jdoh             ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS_M		=	SRCS/main.c SRCS/prompt.c SRCS/minishell_utils1.c \
				SRCS/minishell_utils2.c \
				SRCS/terminal.c SRCS/signal.c SRCS/builtin/builtin_functions1.c \
				SRCS/builtin/builtin_functions2.c SRCS/builtin/builtin.c \
				SRCS/env/env_utils1.c SRCS/env/env_utils2.c SRCS/env/env_utils3.c \
				SRCS/doublylinkedlist1.c SRCS/doublylinkedlist2.c \
				SRCS/doublylinkedlist3.c \
				SRCS/new_parser/del_unused.c SRCS/new_parser/get_pseudo_token.c \
				SRCS/new_parser/group_compound.c SRCS/new_parser/lexer.c \
				SRCS/new_parser/make_ast_utils1.c \
				SRCS/new_parser/make_ast_utils2.c SRCS/new_parser/make_ast.c \
				SRCS/new_parser/parser_utils1.c \
				SRCS/new_parser/parser_utils2.c SRCS/new_parser/parser.c \
				SRCS/new_parser/production.c \
				SRCS/new_parser/pseudo_expand_env.c SRCS/new_parser/stack.c \
				SRCS/new_parser/syntax_check_utils1.c \
				SRCS/new_parser/syntax_check_utils2.c \
				SRCS/new_parser/syntax_check.c \
				SRCS/new_parser/syntax_error.c SRCS/new_parser/tree.c \
				SRCS/executive/execute.c SRCS/executive/execute_utils1.c \
				SRCS/executive/execute_utils2.c SRCS/executive/execute_utils3.c \
				SRCS/executive/open_file.c \
				SRCS/executive/expand.c SRCS/executive/redirect.c \
				SRCS/executive/execute_pipe.c SRCS/executive/here_doc.c \
				SRCS/executive/init_pipe.c \
				SRCS/wildcard/wildcard.c SRCS/wildcard/wildcard_utils.c \
				SRCS/wildcard/discriminate.c
OBJS_M		=	$(SRCS_M:.c=.o)
HEADER_M	=	SRCS/minishell.h SRCS/builtin/builtin.h SRCS/executive/execute.h \
				SRCS/wildcard/wildcard.h SRCS/new_parser/parser.h

SRCS_B		=	BONUS_SRCS/main_bonus.c BONUS_SRCS/prompt_bonus.c \
				BONUS_SRCS/minishell_utils1_bonus.c \
				BONUS_SRCS/minishell_utils2_bonus.c \
				BONUS_SRCS/terminal_bonus.c BONUS_SRCS/signal_bonus.c \
				BONUS_SRCS/builtin/builtin_functions1_bonus.c \
				BONUS_SRCS/builtin/builtin_functions2_bonus.c \
				BONUS_SRCS/builtin/builtin_bonus.c \
				BONUS_SRCS/env/env_utils1_bonus.c \
				BONUS_SRCS/env/env_utils2_bonus.c \
				BONUS_SRCS/env/env_utils3_bonus.c \
				BONUS_SRCS/doublylinkedlist1_bonus.c \
				BONUS_SRCS/doublylinkedlist2_bonus.c \
				BONUS_SRCS/doublylinkedlist3_bonus.c \
				BONUS_SRCS/new_parser/del_unused_bonus.c \
				BONUS_SRCS/new_parser/get_pseudo_token_bonus.c \
				BONUS_SRCS/new_parser/group_compound_bonus.c \
				BONUS_SRCS/new_parser/lexer_bonus.c \
				BONUS_SRCS/new_parser/make_ast_utils1_bonus.c \
				BONUS_SRCS/new_parser/make_ast_utils2_bonus.c \
				BONUS_SRCS/new_parser/make_ast_bonus.c \
				BONUS_SRCS/new_parser/parser_utils1_bonus.c \
				BONUS_SRCS/new_parser/parser_utils2_bonus.c \
				BONUS_SRCS/new_parser/parser_bonus.c \
				BONUS_SRCS/new_parser/production_bonus.c \
				BONUS_SRCS/new_parser/pseudo_expand_env_bonus.c \
				BONUS_SRCS/new_parser/stack_bonus.c \
				BONUS_SRCS/new_parser/syntax_check_utils1_bonus.c \
				BONUS_SRCS/new_parser/syntax_check_utils2_bonus.c \
				BONUS_SRCS/new_parser/syntax_check_bonus.c \
				BONUS_SRCS/new_parser/syntax_error_bonus.c \
				BONUS_SRCS/new_parser/tree_bonus.c \
				BONUS_SRCS/executive/execute_bonus.c \
				BONUS_SRCS/executive/execute_utils1_bonus.c \
				BONUS_SRCS/executive/execute_utils2_bonus.c \
				BONUS_SRCS/executive/execute_utils3_bonus.c \
				BONUS_SRCS/executive/open_file_bonus.c \
				BONUS_SRCS/executive/expand_bonus.c \
				BONUS_SRCS/executive/redirect_bonus.c \
				BONUS_SRCS/executive/execute_pipe_bonus.c \
				BONUS_SRCS/executive/here_doc_bonus.c \
				BONUS_SRCS/executive/init_pipe_bonus.c \
				BONUS_SRCS/wildcard/wildcard_bonus.c \
				BONUS_SRCS/wildcard/wildcard_utils_bonus.c \
				BONUS_SRCS/wildcard/discriminate_bonus.c
OBJS_B		=	$(SRCS_B:.c=.o)
HEADER_B	=	BONUS_SRCS/minishell_bonus.h BONUS_SRCS/builtin/builtin_bonus.h \
				BONUS_SRCS/executive/execute_bonus.h \
				BONUS_SRCS/wildcard/wildcard_bonus.h \
				BONUS_SRCS/new_parser/parser_bonus.h

LIB_FT		=	libft/libft.a

RL_LINK_FLAG	=	-L/Users/jdoh/.brew/opt/readline/lib
RL_COMP_FLAG	=	-I/Users/jdoh/.brew/opt/readline/include

CFLAGS		=	-Werror -Wextra -Wall
BONUS_MODE	=	$(findstring bonus, $(MAKECMDGOALS))

ifeq (bonus, $(BONUS_MODE))
	SRCS	=	$(SRCS_B)
	OBJS	=	$(OBJS_B)
	HEADER	=	$(HEADER_B)
else
	SRCS	=	$(SRCS_M)
	OBJS	=	$(OBJS_M)
	HEADER	=	$(HEADER_M)
endif

all			:	$(NAME)
bonus		:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -L$(dir $(LIB_FT)) -lft $(RL_LINK_FLAG) -lreadline -o $@

$(LIB_FT)	:
	make -C $(dir $(LIB_FT)) bonus

%.o			:	%.c
	$(CC) $(CFLAGS) $(RL_COMP_FLAG) -c $< -o $@

clean		:
	rm -rf $(OBJS_M) $(OBJS_B)

fclean		:	clean
	rm -rf $(NAME)

re			:
	make fclean
	make all

.PHONY		:	all bonus clean fclean re