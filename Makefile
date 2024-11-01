#______command and their flags______#
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
AR = ar -crs
LIBFT_DIR = /libft/include
LIB = libft
SRC_DIR = src
#______files______#
FILES = main.c parse.c check_algo.c win_func.c
#______patterns and substitutions based on BONUS variable______#
SOURCES := $(addprefix $(SRC_DIR)/, $(FILES))
OBJECTS := $(SOURCES:.c=.o)
#______Compilation process______#
NAME = map_checker

# Default rule
all: $(NAME)

$(LIB)/libft.a:
	$(MAKE) -C $(LIB) all
$(NAME): $(OBJECTS) libmlx_Linux.a libft/libft.a 
	$(CC) $(CFLAGS) $^ -o $@ -lXext -lX11 -lm -lz

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#______cleaning______#
clean:
	$(RM) $(OBJECTS) $(OBJECTS_B)
	$(MAKE) -C $(LIB) clean


fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB) fclean
re: fclean all

.PHONY: all clean fclean re bonus