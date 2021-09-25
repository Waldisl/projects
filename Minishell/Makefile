NAME				= minishell

CC					= gcc
CFLAGS  			= -Wall -Wextra -Werror
RM					= rm -rf
LIBS				= -L ./libft -lft -lreadline

HEADER_FILE 		= minishell.h \
						struct.h \

FOLDER				= src/
FOLDER_PARS			= src/pars/
FOLDER_EXEC			= src/exec/
FOLDER_UTILS		= src/utils/
FOLDER_HEADER		= includes/

SRCS				= main.c \
						ft_start_minishell.c \

SRCS_PARS			= ft_get_cmd.c \
						ft_update_t_pars.c \
						ft_check_cmd.c \
						ft_pars.c \
						ft_add_args.c \
						ft_check_pars_str.c \
						ft_str_replace.c \
						ft_delete_pars_str.c \

SRCS_EXEC			= ft_exec_cmd.c \
						ft_overwrite_env.c \
						ft_check_is_simple_cmd.c \
						ft_check_is_multi_cmd.c \
						builtins/ft_exec_builtins.c \
						builtins/ft_cmd_pwd.c \
						builtins/ft_cmd_echo.c \
						builtins/ft_cmd_cd.c \
						builtins/ft_cmd_env.c \
						builtins/ft_cmd_exit.c \
						builtins/ft_cmd_export.c \
						builtins/ft_cmd_unset.c \
						redirections/ft_exec_redir.c \
						redirections/ft_exec_redir_left.c \
						redirections/ft_exec_redir_right.c \
						redirections/ft_exec_pipe.c \

SRCS_UTILS			= ft_history.c \
						ft_print_error.c \
						ft_utils_all.c \
						ft_utils_built_1.c \
						ft_utils_built_2.c \
						ft_utils_free.c \
						ft_utils_redir.c \
						ft_utils_pars.c \

SRC					= $(addprefix ${FOLDER},${SRCS})
SRC_PARS			= $(addprefix ${FOLDER_PARS},${SRCS_PARS})
SRC_EXEC			= $(addprefix ${FOLDER_EXEC},${SRCS_EXEC})
SRC_UTILS			= $(addprefix ${FOLDER_UTILS},${SRCS_UTILS})
HEADERS				= $(addprefix ${FOLDER_HEADER},${HEADER_FILE})

OBJS				= ${SRC:.c=.o}
OBJS_PARS			= ${SRC_PARS:.c=.o}
OBJS_EXEC			= ${SRC_EXEC:.c=.o}
OBJS_UTILS			= ${SRC_UTILS:.c=.o}

MAKE_EXT			= @make -s --no-print-directory -C

HISTORY_FILE		= $(HOME)/.minishell_history
UNAME_S				= $(shell uname -s)

COMPILE 		= $(CC) $(CFLAGS) ${OBJ} $(LIBS) -o $(NAME)
LOGDATE 		= $(shell date --iso=seconds)

OBJ					= ${OBJS} ${OBJS_PARS} ${OBJS_EXEC} ${OBJS_UTILS}

$(NAME):	${OBJ}
			@$(MAKE_EXT) ./libft
			@$(READLINE)
			@printf "Minishell compiling\n"
			@$(COMPILE)
			

all:		${NAME}

%.o: %.c	$(HEADERS)
			@printf "Creating objects files: %-33.33s\r" $@
			@$(CC) -c $(CFLAGS) -o $@ $<

re: 		fclean all

clean:
			$(MAKE_EXT) ./libft clean
			@${RM} ${OBJ}
			@printf "Minishell cleaning\n"

fclean:		clean
			$(MAKE_EXT) ./libft fclean
			@${RM} $(NAME) $(HISTORY_FILE)
			@printf "Minishell full cleaning\n"

.PHONY: 	all clean fclean re 
