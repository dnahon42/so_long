# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 14:05:47 by dnahon            #+#    #+#              #
#    Updated: 2025/06/20 15:49:04 by dnahon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	so_long
CC 			= 	cc
CFLAGS 		= 	-g3 -Wall -Wextra -Werror -Imlx_linux -I./includes

LDFLAGS		= 	-Llibft -lft
AR 			= 	ar rcs
RM 			= 	rm -f
SRC_DIR 	= 	./src/so_long
SRC 		= 	./src/so_long/so_long.c ./src/so_long/so_long_utils.c \
				./src/so_long/free.c ./src/so_long/initialize_game.c \
				./src/so_long/movement.c ./src/so_long/ui.c \
				./src/so_long/map_validity.c ./src/so_long/map_validity2.c \
				./src/so_long/key_handler.c ./src/so_long/so_long_utils2.c\

INCLUDES	= 	./includes/so_long.h ./includes/libft.h ./includes/ft_printf.h ./includes/get_next_line.h
MLX 		= 	./minilibx-linux/libmlx.a -lXext -lX11
LIBFT		=	./libft/libft.a

OBJ 		= 	$(SRC:.c=.o)

# Color codes
GREEN 		= 	\033[0;32m
YELLOW 		= 	\033[0;33m
RED			= 	\033[0;31m
BLUE 		= 	\033[0;34m
PURPLE 		= 	\033[0;35m
CYAN 		= 	\033[0;36m
NC 			= 	\033[0m # No Color

all: mlx $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libft --no-print-directory
	@echo "$(GREEN)Building $(NC)$(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) $(MLX)

mlx:
	@echo "$(YELLOW)Compiling MiniLibX$(NC)"
	@$(MAKE) -C minilibx-linux --no-print-directory

%.o: %.c $(INCLUDES)
	@echo "$(CYAN)Compiling $(NC)$<"
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(MAKE) -C libft clean --no-print-directory
	@echo "$(CYAN)Cleaning object files"
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) -C libft fclean --no-print-directory
	@echo "$(CYAN)Cleaning $(NC)$(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx