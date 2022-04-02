NAME	= Array

CXX		= clang++ -std=c++98

FLAGS	= -Wall -Wextra -Werror

SRCS = main.cpp

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