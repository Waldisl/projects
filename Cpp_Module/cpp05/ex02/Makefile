NAME	= Bureaucrat

CXX		= clang++ -std=c++98

FLAGS	= -Wall -Wextra -Werror

SRCS = main.cpp Bureaucrat.cpp Form.cpp PresidentialPardonForm.cpp RobotomyRequestForm.cpp ShrubberyCreationForm.cpp

all: $(NAME)

$(NAME): $(SRCS)
	@$(CXX) $(FLAGS) $(SRCS) -o $(NAME) 
	@echo "Run ./$(NAME)"

clean:
	@echo "No object files"

fclean :
	@ rm -f $(NAME)
	@ rm -f *_shrubbery
	@echo "Project $(NAME) deleted!"

re : fclean all

.PHONY : all clean fclean re