NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ../minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I$(MLX_DIR) -I../libft
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re