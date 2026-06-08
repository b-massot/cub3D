# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#   Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#              #
#   Updated: 2026/06/08 10:00:00 by ajeanren         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d_adri
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I $(INCDIR) -I $(LIBFT_DIR)
SRCDIR		= sources
INCDIR		= includes
LIBFT_DIR	= ../libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_FILES	= main_adri.c \
			  error_adri.c \
			  checker_adri.c \
			  utils_adri.c \
			  free_map_adri.c \
			  parsing_main_adri.c \
			  color_parser_adri.c \
			  texture_parser_adri.c \
			  color_extractor_adri.c \
			  texture_extractor_adri.c \
			  parsing_identifiers_adri.c \
			  grid_extractor_adri.c \
			  validation_adri.c

SRCS		= $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJS		= $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(NAME) compiled successfully!"

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

 fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.SILENT:
.PHONY: all clean fclean re
