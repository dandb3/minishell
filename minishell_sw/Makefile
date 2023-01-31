# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 19:25:02 by jdoh              #+#    #+#              #
#    Updated: 2023/01/31 17:24:10 by sunwsong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS_M		=	main.c prompt.c token.c minishell_utils.c \
				builtin/builtin_functions1.c builtin/builtin_functions2.c \
				builtin/builtin.c env/env_utils1.c env/env_utils2.c\
				doublylinkedlist1.c doublylinkedlist2.c \
				signal.c
				
OBJS_M		=	$(SRCS_M:.c=.o)
HEADER_M	=	minishell prompt builtin/builtin

# SRCS_B		=	main_bonus.c init_bonus.c error_bonus.c parsing_bonus.c \
# 				pipex_bonus.c process_bonus.c get_next_line_bonus.c \
# 				fileopen_bonus.c
# OBJS_B		=	$(SRCS_B:.c=.o)
# HEADER_B	=	pipex_bonus.h

LIBFT		=	libft/libft.a
LIBFT_DIR	=	libft

RL_LINK_FLAG		= -lreadline -L $(HOME)/goinfre/.brew/Cellar/readline/8.2.1/lib
RL_COMP_FLAG	= -I $(HOME)/goinfre/.brew/Cellar/readline/8.2.1/include

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

$(NAME)		:	$(OBJS)
	$(CC) $(CFLAGS) $(RL_LINK_FLAG) $(OBJS) libft.a -lreadline -o $@
	

# $(NAME)		:	$(OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -lreadline -o $@

$(LIBFT)	:
	make -C $(LIBFT_DIR) bonus

%.o			:	%.c
	$(CC) $(CFLAGS) $(RL_COMP_FLAG) -c $< -o $@

clean		:
	rm -rf $(OBJS_M) $(OBJS_B)
#	make -C $(LIBFT_DIR) fclean

fclean		:	clean
	rm -rf $(NAME)

re			:
	make fclean
	make all

.PHONY		:	all bonus clean fclean re