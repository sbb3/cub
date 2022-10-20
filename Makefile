CC = gcc
# -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS =  -I../incl/
#  -g3 -fsanitize=address
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

LIBFTPATH = ./srcs/libft/libft.a

RM = rm -rf

COLOUR_BLUE=\033[0;35m


SRCS = ./srcs/cub3d/cub3d.c \
	./srcs/cub3d/Parser.c \
	./srcs/cub3d/init.c \
	./srcs/cub3d/Render.c \
	./srcs/cub3d/minimap.c \
	./srcs/cub3d/tools.c \
	./srcs/cub3d/movements.c \
	./srcs/cub3d/imageHelpers.c \
	./srcs/cub3d/renderUtils.c \
	./srcs/cub3d/quit.c \
	./srcs/gnl/get_next_line.c

OBJS = $(SRCS:%.c=%.o)

NAME = cub3d

$(VERBOSE).SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./srcs/libft/
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFTPATH) -o $(NAME)
	@echo "👉 $(COLOUR_BLUE)COMPILING DONE$(COLOUR_END) 👈"

%.o : %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) ./srcs/libft/*.o
	@make clean -C ./srcs/libft/

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./srcs/libft/

re: fclean all
