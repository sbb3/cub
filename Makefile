CC = gcc -Wall -Wextra -Werror

CFLAGS =  -I../incl/ -g
#  -g3 -fsanitize=address
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

COLOUR_BLUE=\033[0;35m


SRCS = ./srcs/Game/Render/Cub3d.c \
	./srcs/Game/Render/Init.c \
	./srcs/Game/Render/Draw/Render.c \
	./srcs/Game/Render/Draw/Paint.c \
	./srcs/Game/Render/Draw/RenderUtils.c \
	./srcs/Game/Render/Draw/RenderUtils2.c \
	./srcs/Game/Render/Draw/RenderUtils3.c \
	./srcs/Game/Render/Draw/Minimap.c \
	./srcs/Game/Render/Movement/Movements.c \
	./srcs/Game/Render/Movement/MovementsHelpers.c \
	./srcs/Game/Render/Movement/MovementsHelpers2.c \
	./srcs/Game/Render/ImageHelpers/ImageHelpers.c \
	./srcs/Game/Render/ImageHelpers/CreateImages.c \
	./srcs/Game/Render/ImageHelpers/GetSetColors.c \
	./srcs/Game/Render/GeneralHelpers.c \
	./srcs/Game/Render/Quit.c \
	./srcs/Game/Parser/autre_function.c \
	./srcs/Game/Parser/cheak_content_map.c \
	./srcs/Game/Parser/cheak.c \
	./srcs/Game/Parser/encoded_color.c \
	./srcs/Game/Parser/get_content.c \
	./srcs/Game/Parser/get.c \
	./srcs/Game/Parser/help_function.c \
	./srcs/Game/Parser/les_cas.c \
	./srcs/Game/Parser/parcing_map.c \


OBJS = $(SRCS:%.c=%.o)

NAME = cub3d

$(VERBOSE).SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS)  -o $(NAME)
	@echo "👉 $(COLOUR_BLUE)COMPILING DONE$(COLOUR_END) 👈"

%.o : %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
