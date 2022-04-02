NAME = FT_cont
STL = STL_cont

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INC = -Iinclude

SRCDIR = src/
SRCS =	main.cpp \

OBJDIR = obj/
OBJ = $(addprefix $(OBJDIR),$(SRCS:.cpp=.o))

OBJDIRSTL = obj_stl/
OBJSTL = $(addprefix $(OBJDIRSTL),$(SRCS:.cpp=.o))

all: $(NAME) $(STL)

ft: $(NAME)

stl: $(STL)

############ NAME
$(NAME): $(OBJDIR) $(OBJ)
	@$(CXX) $(INC) $(OBJ) -o $(NAME)
	@echo Run ./$(NAME)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@$(CXX) $(CXXFLAGS) -DFT=ft $(INC) -c $< -o $@

################## STL
$(STL): $(OBJDIRSTL) $(OBJSTL)
	@$(CXX) $(INC) $(OBJSTL) -o $(STL)
	@echo Run ./$(STL)

$(OBJDIRSTL):
	@mkdir -p $@

$(OBJDIRSTL)%.o: $(SRCDIR)%.cpp
	@$(CXX) $(CXXFLAGS) -DFT=std $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJDIR) $(OBJDIRSTL)

fclean: clean
	@rm -rf $(NAME) $(STL)

re: clean fclean all
