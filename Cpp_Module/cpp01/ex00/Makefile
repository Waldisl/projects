NAME	= zombie

CC		= clang++

FLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp newZombie.cpp randomChump.cpp Zombie.cpp

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
	@echo "Run ./$(NAME)"

clean:
	@echo "No object files"

fclean :
	@ rm -f $(NAME)
	@echo "Project $(NAME) deleted!"

re : fclean all

.PHONY : all clean fclean re