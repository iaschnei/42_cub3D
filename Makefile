# ---------------------------------------------------------------------------- #

SRCS		=	src/main.c src/utils/utils.c src/utils/vector_utils.c src/utils/coord_utils.c \
				src/utils/ft_atoi_base.c src/parsing/parsing.c src/parsing/map_file_check.c \
				src/parsing/check_map_lines.c src/parsing/check_text_lines.c src/parsing/check_useless_lines.c \
				src/parsing/parsing_utils.c src/parsing/assignation.c \
				src/parsing/xpm_parsing.c src/parsing/xpm_parsing_bis.c \
				src/render/render.c src/render/input.c src/render/game_exit.c src/render/image.c \
				src/render/print_default.c src/render/framerate.c src/render/minimap.c \
				src/render/movement.c src/render/print_wall.c src/render/raycasting.c src/render/raycasting_utils.c \
				src/render/rotation.c src/render/player_distances.c src/render/movement_bis.c \
				src/parsing/assignation_textures.c src/parsing/check_map_lines_bis.c
# ---------------------------------------------------------------------------- #

OBJS		=	$(SRCS:.c=.o)

DEPS		=	$(SRCS:.c=.d)

CC			=	cc

INCL		=	src/cub3d.h

LIBFT		=	src/libft/libft.a

FLAGS		=	-MMD -MP

MLXFLAGS	=	-Lminilibx-linux -lmlx_Linux -lXext -lX11 -Lmlx -lm

NAME		=	cub3D

MLX			=	./minilibx-linux/libmlx.a

COLOR_GREEN	=	\033[1;32m
COLOR_RED	=	\033[1;31m
COLOR_BLUE	=	\033[3;36m
COLOR_PURP	=	\033[1;35m
COLOR_END	=	\033[0m

%.o: %.c
	@$(CC) $(FLAGS) -include $(INCL) -I/usr/include -g -Iminilibx-linux -O3 -c $< -o $@
	@echo "$(COLOR_BLUE) || Compiling ($<)...$(COLOR_END)"

all: $(NAME)

$(LIBFT): $(INCL)
	@$(MAKE) -C src/libft
	@echo "$(COLOR_GREEN) || Compiled libft !$(COLOR_END)"

$(MLX):
	@cd ./minilibx-linux && sh ./configure && cd ..

$(NAME): $(OBJS) $(INCL) $(LIBFT) $(MLX)
	@$(CC) $(OBJS) -o $(NAME) $(MLXFLAGS) $(LIBFT)
	@echo "$(COLOR_GREEN) || Done !$(COLOR_END)"

clean:
	@rm -rf $(OBJS)
	@$(MAKE) -C src/libft clean
	@echo "$(COLOR_RED) || Cleaning files...$(COLOR_END)"

fclean: clean
	@rm -rf $(NAME) $(DEPS)
	@$(MAKE) -C src/libft fclean
	@echo "$(COLOR_RED) || Cleaning library...$(COLOR_END)"

re: fclean all

.PHONY: re fclean all clean

-include $(DEPS)
