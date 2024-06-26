#COLORS
NC		=	\033[0m
LRED	=	\033[0;31m
LREDB	=	\033[1;31m
GREEN	=	\033[1;32m
LGREEN	=	\033[1;92m
PINK	=	\033[1;95m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
LBLUE	=	\033[1;36m

CC = gcc
CFLAGS = -Werror -Wextra -Wall
NAME = minirt
LIBFT_PATH = libft/
MLX_PATH = mlx-linux/
LIBFT = libft/libft.a
LINK_LIBFT = -lft -L ./libft
SHAPES = sphere.c plane.c cylinder.c cylinder2.c
PARSE = reader.c parser.c parsers.c parsers2.c
UTILS = ft_haschar.c ft_splitlen.c ft_atod.c ft_error.c converters.c ft_is_normalized.c print_scene.c ft_is_empty.c
MATH = math_functions.c math_functions2.c math_functions3.c
SRC = main.c hooks.c functions.c scene.c scene2.c colors.c colors2.c render.c render2.c lights.c
SRCS = $(addprefix src/, $(SRC)) \
		$(addprefix src/shapes/, $(SHAPES)) \
		$(addprefix src/parse/, $(PARSE)) \
		$(addprefix src/utils/, $(UTILS)) \
		$(addprefix src/math/, $(MATH))
OBJS_PATH = objs/
OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
ifeq ($(shell uname), Linux)
	MLXFLAGS = -lmlx -lXext -lX11 -lm -lz -L ./mlx-linux -lpthread
else
	MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(LINK_LIBFT):
	make -C $(LIBFT_PATH)
	make -C $(MLX_PATH)

$(OBJS_PATH):
	@mkdir -p $(dir $(OBJS))

$(OBJS_PATH)%.o: %.c | $(OBJS_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH) $(OBJS) $(LINK_LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LINK_LIBFT) -o $@ $(MLXFLAGS)
	@clear
	@echo "MINIRT COMPILED"

clean: 
	rm -f *.o
	rm -rf objs
	make fclean -C $(LIBFT_PATH)
fclean: clean
	rm $(NAME)

re: fclean all