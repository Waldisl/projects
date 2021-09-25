# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msunspot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 21:09:29 by msunspot          #+#    #+#              #
#    Updated: 2021/09/14 00:33:12 by msunspot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC	=	src/phil.c \
			src/thread.c \
			src/utils.c \
			src/utils1.c \

OBJS	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			gcc $(CFLAGS) -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
