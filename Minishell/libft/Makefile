NAME 		= libft.a
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror
RM 			= rm -rf
AR 			= ar rcs

OBJS 		= 	ft_atoi.o \
				ft_bzero.o \
				ft_calloc.o \
				ft_isalnum.o \
				ft_isalpha.o \
				ft_isascii.o \
				ft_isdigit.o \
				ft_islower.o \
				ft_isprint.o \
				ft_isspace.o \
				ft_isupper.o \
				ft_itoa.o \
				ft_memccpy.o \
				ft_memchr.o \
				ft_memcmp.o \
				ft_memcpy.o \
				ft_memmove.o \
				ft_memset.o \
				ft_putchar_fd.o \
				ft_putendl_fd.o \
				ft_putnbr_fd.o \
				ft_putstr_fd.o \
				ft_split.o \
				ft_strchr.o \
				ft_strdup.o \
				ft_strjoin.o \
				ft_strlcat.o \
				ft_strlcpy.o \
				ft_strlen.o \
				ft_strmapi.o \
				ft_strncmp.o \
				ft_strnstr.o \
				ft_strrchr.o \
				ft_strtrim.o \
				ft_substr.o \
				ft_tolower.o \
				ft_toupper.o \
				get_next_line.o

$(NAME): 	$(OBJS)
			@printf "                                                                         \r"
			@$(AR) $@ $^

.c.o:
			@printf "Compile libft: %-33.33s\r" $@
			@$(CC) $(CFLAGS) -c -o $@ $<

all: 		$(NAME)

clean:
			@$(RM) $(OBJS)

fclean: 	clean
			@$(RM) $(NAME)

re: 		clean all

.PHONY: 	all clean fclean re
