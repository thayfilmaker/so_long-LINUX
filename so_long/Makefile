# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 05:55:33 by sousa             #+#    #+#              #
#    Updated: 2025/09/20 22:23:29 by thasousa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long

SRC		= src/main.c \
		  src/graphics.c \
		  src/player.c \
		  src/player_utils.c \
		  src/map.c \
		  src/validate_map.c \
		  src/validate_utils.c \
		  src/utils.c \
		  src/path.c \
		  src/path_utils.c \
		  src/path_utils2.c

OBJ		= $(SRC:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

all: $(MLX) $(NAME)

$(MLX):
	git clone https://github.com/42paris/minilibx-linux.git
	$(MAKE) -C $(MLX_DIR) all

$(NAME): $(OBJ) $(MLX)
	$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf minilibx-linux

re: fclean all

norm:
	norminette $(SRC) include/so_long.h
