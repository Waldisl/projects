# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msunspot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/24 13:04:06 by msunspot          #+#    #+#              #
#    Updated: 2021/04/22 23:58:21 by msunspot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	cub3d.c \
		errors.c \
		gnl_mod.c \
		gnl_utils.c \
		init_more.c \
		init.c \
		mlx_raycast.c \
		mlx_utils.c \
		pars_color.c \
		pars_map.c \
		pars_texture.c \
		parser.c \
		raycast_key.c \
		raycast_sprite.c \
		raycast_utils.c \
		utils_more.c \
		utils.c

NAME = Cub3D

MLX_DIR = minilibx-linux
MLX = libmlx.a 
CC = gcc

CFLAGS = -Wall -Wextra -Werror -g 

OBJ_DIR = src/obj
SRC_DIR = src

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}

all:
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
		@echo $(NAME) : Created !

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@rm -rf $(OBJ_DIR)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re

-include $(DPD)
