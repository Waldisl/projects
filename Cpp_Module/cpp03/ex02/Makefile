NAME	= FragTrap

CXX		= clang++

FLAGS	= -Wall -Wextra -Werror

SRCS = main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp

all: $(NAME)

$(NAME): $(SRCS)
	@$(CXX) $(FLAGS) $(SRCS) -o $(NAME) 
	@echo "Run ./$(NAME)"

clean:
	@echo "No object files"

fclean :
	@ rm -f $(NAME)
	@echo "Project $(NAME) deleted!"

re : fclean all

.PHONY : all clean fclean re