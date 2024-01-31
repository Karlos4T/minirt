
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
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
NAME = minirt
SRC = main.c
SRCS = $(addprefix src/, $(SRC))
OBJS_PATH = objs/
OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))


all: $(NAME)

$(OBJS_PATH):
	mkdir -p $(dir $(OBJS))

$(OBJS_PATH)%.o: %.c | $(OBJS_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) -o $@
	@clear
	@echo "MINIRT COMPILED"

clean: 
	rm -f *.o
	rm -rf objs

fclean: clean
	rm $(NAME)

re: fclean all