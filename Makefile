

CC = gcc
CFLAGS = -Werror -Wextra -Wall
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
NAME = minirt

SRCS = main.c
SRC = src/




all: $(NAME)

#$(OBJS_PATH)
#	mkdir -p $<

#$(OBJS_PATH)%.o: %.c | $(OBJS_PATH)


$(NAME):
	$(CC) $(CFLAGS) $(MLXFLAGS) main.c -o $<

clean: 
	rm -f *.o