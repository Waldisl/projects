
NAME = libftprintf.a
LIBFT = libft.a
LIBFTFOLDER = libft/

SRC = ft_printf.c \
	ft_pars.c \
	ft_printf_utils.c \
	ft_type_c_.c \
	ft_type_di_.c \
	ft_type_p_.c \
	ft_type_procent_.c \
	ft_type_s_.c \
	ft_type_u_.c \
	ft_type_x_.c \
	ft_processor.c

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFTFOLDER)
	@cp $(LIBFTFOLDER)$(LIBFT) $(NAME)
	@ar rcs $(NAME) $?

%.o : %.c
	gcc $(FLAGS) -I . -c $< -o $@

main:	re
		@gcc main.c libftprintf.a -I ft_printf.h $(FLAGS)

mainclean:
			@rm -f main.o
			@rm -f a.out

clean_printf:
		@rm -f $(OBJ)

fclean_printf: clean_printf
		@rm -f $(NAME)

clean_libft:
		@$(MAKE) -C $(LIBFTFOLDER) clean

fclean_libft:
		@$(MAKE) -C $(LIBFTFOLDER) fclean

clean: clean_printf clean_libft

fclean:	fclean_printf fclean_libft

re:		fclean all

.PHONY: all clean fclean re clean_libft clean_printf fclean_libft fclean_printf
