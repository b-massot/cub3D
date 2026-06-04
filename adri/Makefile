# Nom de l'exécutable
NAME        = cub3d_adri

# Compilateur et flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I $(INCDIR) -I $(LIBFT_DIR)

# Dossiers du projet
SRCDIR      = sources
INCDIR      = includes

# Configuration de la Libft (dossier parent d'où le '../')
LIBFT_DIR   = ../libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Liste de tes fichiers sources
SRC_FILES   = main_adri.c error_adri.c checker_adri.c parsing_adri.c utils_adri.c

# Reconstruction des chemins complets
SRCS        = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJS        = $(SRCS:.c=.o)

# Règle par défaut
all: $(LIBFT) $(NAME)

# Compilation de la libft en appelant son propre Makefile
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compilation de l'exécutable avec la libft
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(NAME) compilé avec succès !"

# Règle générique pour les fichiers objets
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets du projet
clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "Fichiers objets supprimés."

# Nettoyage complet (projet + libft)
fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Exécutables et archives supprimés."

# Recommencer à zéro
re: fclean all

.SILENT:
.PHONY: all clean fclean re