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
LIBFT = libft/libft.a
SHAPES = sphere.c plane.c cylinder.c
PARSE = reader.c
SRC = main.c math_functions.c functions.c scene.c scene2.c colors.c render.c
SRCS = $(addprefix src/, $(SRC)) \
		$(addprefix src/shapes/, $(SHAPES)) \
		$(addprefix src/parse/, $(PARSE))
OBJS_PATH = objs/
OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
ifeq ($(shell uname), Linux)
	MLXFLAGS = -lmlx -lXext -lX11 -lm -lz -L ./mlx-linux -lpthread
else
	MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJS_PATH):
	@mkdir -p $(dir $(OBJS))

$(OBJS_PATH)%.o: %.c | $(OBJS_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(MLXFLAGS)
	@clear
	@echo "MINIRT COMPILED"

clean: 
	rm -f *.o
	rm -rf objs
	make fclean -C $(LIBFT_PATH)
fclean: clean
	rm $(NAME)

re: fclean all