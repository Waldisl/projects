# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msunspot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 16:27:42 by msunspot          #+#    #+#              #
#    Updated: 2020/11/18 22:49:38 by msunspot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libft.a
FLAGS      = -Wall -Werror -Wextra -I. -c
FILES       = ft_strlen.c \
                ft_strchr.c \
                ft_strncmp.c \
                ft_atoi.c \
                ft_isalpha.c \
                ft_isdigit.c \
                ft_isalnum.c \
                ft_isprint.c \
                ft_toupper.c \
                ft_tolower.c \
                ft_isascii.c \
				ft_memset.c \
                ft_strdup.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_calloc.c \
				ft_strrchr.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strmapi.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_itoa.c \
				ft_strtrim.c \
				ft_split.c \

FILES_BONUS =	ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstnew.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \

OBJ         = $(FILES:%.c=%.o)

OBJ_BONUS	= $(FILES_BONUS:%.c=%.o)

all: $(NAME)

$(NAME): 
	gcc $(FLAGS) $(FILES)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	gcc $(FLAGS) $(FILES) $(FILES_BONUS)
	ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

.PHONY: clean fclean all re
