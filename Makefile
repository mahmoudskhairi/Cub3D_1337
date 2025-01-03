# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 15:54:37 by rmarzouk          #+#    #+#              #
#    Updated: 2024/11/20 16:43:38 by rmarzouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 # -fsanitize=address
MLX_FALGS=utils/MLX42/build/libmlx42.a utils/MLX42/build/libglfw3.a
LIBS = -framework Cocoa -framework OpenGL -framework IOKit
LIBFT_FLAGS = -L utils/libft -lft

NAME = cub3D

PARSING_DIR = src/parsing/
S_PARSING= $(addprefix $(PARSING_DIR), ft_requirements.c\
									ft_textures.c\
									ft_colors.c\
									ft_map.c\
									ft_map_utils.c\
								)

O_PARSING = $(S_PARSING:.c=.o)

GAME_DIR = src/game/
S_GAME= $(addprefix $(GAME_DIR), ft_init_mlx.c\
											render_map.c \
											mouvements.c \
											projection_3D.c \
											ft_player.c \
											mini_map.c \
								)

O_GAME = $(S_GAME:.c=.o)

all: $(NAME)

$(NAME): $(NAME).o $(O_PARSING) $(O_GAME)
	make -C utils/libft
	$(CC) $(CFLAGS) $(MLX_FALGS) $(LIBS) $(LIBFT_FLAGS) $(NAME).o $(O_GAME) $(O_PARSING) -o $(NAME)

%.o:%.c cube3d.h
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	# make fclean -C utils/libft
	rm -f $(NAME).o 
	rm -fr $(O_PARSING) $(O_GAME)

fclean: clean
	rm -f $(NAME)

re: fclean all
