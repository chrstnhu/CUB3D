# Path to libraries
MLX_PATH = ./minilibx_linux/
LIBFT_PATH = ./libft
LIBS_PATH = -L$(LIBFT_PATH) -L$(MLX_PATH)
SRCS_PATH = srcs
OBJ_DIR	= obj
OBJ_BONUS_DIR = obj_bonus

# Source mandatory
CHECK = check_rgb_color.c check_cub_file.c check_map.c check_border_map.c check_cub_utils.c
INIT = init.c init_player_dir.c init_texture.c
PARSING = parse_cub_file.c parse_map.c parse_tex.c parse_utils.c
PLAYER = player_move.c validate_move.c
RENDER = raycasting.c raycasting_utils.c render.c handler_key.c
UTILS = utils.c error.c free.c 

SRCS = $(CHECK:%=srcs/check/%) $(INIT:%=srcs/init/%) \
	$(PARSING:%=srcs/parsing/%) $(PLAYER:%=srcs/player/%) \
	$(RENDER:%=srcs/render/%) $(UTILS:%=srcs/utils/%) \
	srcs/main.c

OBJS = $(SRCS:$(SRCS_PATH)/%.c=$(OBJ_DIR)/%.o)

# Source bonus
PLAYER_BONUS = player_move_bonus.c validate_move_bonus.c
RENDER_BONUS = raycasting.c raycasting_utils.c render.c handler_key.c handler_mouse_bonus.c

SRCS_BONUS = $(CHECK:%=srcs/check/%) $(INIT:%=srcs/init/%) \
	$(PARSING:%=srcs/parsing/%) $(PLAYER_BONUS:%=srcs/player/%) \
	$(RENDER_BONUS:%=srcs/render/%) $(UTILS:%=srcs/utils/%)\
	srcs/main_bonus.c

OBJS_BONUS = $(SRCS_BONUS:$(SRCS_PATH)/%.c=$(OBJ_BONUS_DIR)/%.o)

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm -lbsd -lft
INCLUDES = -I$(LIBFT_PATH) -I$(MLX_PATH) 

NAME = cub3D
NAME_BONUS = cub3D_bonus

# Create a objet directory
$(OBJ_DIR)/%.o: $(SRCS_PATH)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	
$(OBJ_BONUS_DIR)/%.o: $(SRCS_PATH)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# Execute
all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) includes/cub3d.h
	make -C $(LIBFT_PATH)
	make -C $(MLX_PATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS_PATH) $(LFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME_BONUS): $(OBJS_BONUS) includes/cub3d.h
	make -C $(LIBFT_PATH)
	make -C $(MLX_PATH)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBS_PATH) $(LFLAGS)

$(OBJ_BONUS_DIR):
	mkdir -p $(OBJ_BONUS_DIR)

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS_DIR)
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f libmlx.a
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
