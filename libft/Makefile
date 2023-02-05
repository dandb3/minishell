# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 12:26:30 by jdoh              #+#    #+#              #
#    Updated: 2023/01/23 19:34:28 by jdoh             ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_strcmp.c \
		ft_printf_utils_1_bonus.c	\
		ft_printf_utils_2_bonus.c	\
		ft_printf_utils_3_bonus.c	\
		print_format_1_bonus.c		\
		print_format_2_bonus.c		\
		print_format_3_bonus.c		\
		ft_printf_bonus.c			\
		struct_init_bonus.c			\
		print_all_bonus.c
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
HEADER = libft.h ft_printf.h
CFLAGS = -Werror -Wextra -Wall

BONUS_MODE = $(findstring bonus, $(MAKECMDGOALS))
OBJS_TOTAL = $(OBJS) $(if $(BONUS_MODE), $(BONUS_OBJS))

all : $(NAME)

bonus : $(NAME)

$(NAME) : $(OBJS_TOTAL) $(HEADER)
	ar -rc $@ $(OBJS_TOTAL) 

%.o : %.c
	cc -c $(CFLAGS) $< -o $@

clean :
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re all bonus
