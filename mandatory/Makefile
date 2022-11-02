CC = gcc

CFLAGS = -Wall -Wextra -Werror -I../incl/
#  -g3 -fsanitize=address
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

COLOUR_BLUE=\033[0;35m

SRCS = ./srcs/game/render/cub3d.c \
	./srcs/game/render/init.c \
	./srcs/game/render/draw/render.c \
	./srcs/game/render/draw/paint.c \
	./srcs/game/render/draw/renderUtils.c \
	./srcs/game/render/draw/renderUtils2.c \
	./srcs/game/render/draw/renderUtils3.c \
	./srcs/game/render/movements/movements.c \
	./srcs/game/render/movements/movementsHelpers.c \
	./srcs/game/render/movements/movementsHelpers2.c \
	./srcs/game/render/movements/movementsHelpers3.c \
	./srcs/game/render/imageHelpers/imageHelpers.c \
	./srcs/game/render/imageHelpers/createImages.c \
	./srcs/game/render/imageHelpers/getSetColors.c \
	./srcs/game/render/generalHelpers.c \
	./srcs/game/render/quit.c \
	./srcs/game/render/free.c \
	./srcs/game/parser/autre_function.c \
	./srcs/game/parser/cheak_content_map.c \
	./srcs/game/parser/cheak.c \
	./srcs/game/parser/encoded_color.c \
	./srcs/game/parser/get_content.c \
	./srcs/game/parser/get.c \
	./srcs/game/parser/help_function.c \
	./srcs/game/parser/les_cas.c \
	./srcs/game/parser/parcing_map.c \

OBJS = $(SRCS:%.c=%.o)

NAME = cub3D

$(VERBOSE).SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)
	@echo "👉 $(COLOUR_BLUE)COMPILING DONE$(COLOUR_END) 👈"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
