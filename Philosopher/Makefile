
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
