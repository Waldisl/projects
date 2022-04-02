NAME = PhoneBook

SRC = function.cpp \
		main.cpp

CFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ = $(SRC:.cpp=.o)

all : $(NAME)

%.o : %.c
	clang++ -c $< -o $@

$(NAME) : $(OBJ)
	clang++ $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re