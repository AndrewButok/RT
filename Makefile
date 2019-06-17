# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abutok <abutok@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/22 16:24:00 by abutok            #+#    #+#              #
#    Updated: 2019/06/17 18:44:33 by abutok           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
PARSON = ./parson/libparson.a
#	C compiler and his default flags
GCC = gcc -Wall -Wextra -Werror -Ofast -flto -pipe -march=native -mtune=native
#	Libft and parson linking
LINKLIBFT = -L ./libft -lft
LINKPARSON = -L ./parson -lparson
#	Libs linking
LINKLIB = -framework OpenGL -framework AppKit $(LINKLIBFT) $(LINKPARSON) -framework OpenCL
#	Sources directories
SRCDIR = ./src/
COLORDIR = ./src/color/
SCENEDIR = ./src/scene_objects/
LIGHTDIR = ./src/light/
VECTORDIR = ./src/vector/
PARSEDIR = ./src/parse/
#	Source files
SRCFILES = main.c cl.c cl2.c sdl_load_image.c
SCENEFILES = sphere.c infinite_plane.c infinite_cone.c infinite_cylinder.c \
				light_init.c cylinder.c cone.c triangle.c ellipsoid.c
VECTORFILES = vector.c
PARSEFILES = ft_hexatoi.c get_space.c  get_sphere.c get_vector.c \
				get_params.c get_figure_params.c get_figure_texture.c \
				get_infinite_plane.c get_infinite_cone.c \
				get_infinite_cylinder.c get_cylinder.c get_cone.c \
				get_triangle.c get_ellipsoid.c\
				get_light.c get_cam.c
				
#	Header folder
INCLUDE = ./includes
#   Header file
HEADER = $(INCLUDE)/rt.h
#	Binaries folder
BINDIR = ./obj/
#	Binaries list
BIN = $(addprefix $(BINDIR), $(SRCFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(SCENEFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(VECTORFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(PARSEFILES:.c=.o))

#	Libft
LIBFT = ./libft/libft.a
#	Libft header
LIBFTINCLUDE = ./libft/includes
#	Parson header
PARSONINCLUDE = ./parson
#	Brew include
BRINCLUDE = -I ~/.brew/include
#	Brew link
BRLINK = -L ~/.brew/lib -rpath ~/.brew/lib -lSDL2 -lSDL2_image

.NOTPARALLEL = all fclean clean re $(NAME)

all: $(LIBFT) $(PARSON) $(NAME)

$(NAME): $(BINDIR) $(BIN)
	$(GCC) $(LINKLIB) -o $(NAME) $(BIN) -I $(LIBFTINCLUDE) -I $(INCLUDE) -I $(PARSONINCLUDE) $(BRINCLUDE) $(BRLINK)

$(BINDIR):
	@if [ ! -d "$(BINDIR)" ]; then mkdir $(BINDIR); fi


$(BINDIR)%.o: $(SRCDIR)%.c $(HEADER)
	$(GCC) -c $(BRINCLUDE) -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(PARSEDIR)%.c $(HEADER)
	$(GCC) -c $(BRINCLUDE) -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(SCENEDIR)%.c $(HEADER)
	$(GCC) -c $(BRINCLUDE) -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(VECTORDIR)%.c $(HEADER)
	$(GCC) -c $(BRINCLUDE) -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

#$(BINDIR)%.o: $(COLORDIR)%.c $(HEADER)
#	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) -I $(SDLINCLUDE) -I $(SDLIINCLUDE) $< -o $@

#$(BINDIR)%.o: $(LIGHTDIR)%.c $(HEADER)
#	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) -I $(SDLINCLUDE) -I $(SDLIINCLUDE) $< -o $@

#

clean:
	make -C ./libft/ clean
	make -C ./parson/ clean
	if [ -d "$(BINDIR)" ]; then rm -rf $(BINDIR); fi

fclean: clean
	make -C ./libft/ fclean
	make -C ./parson/ fclean
	if [ -f "$(NAME)" ]; then rm -rf $(NAME); fi

re: fclean all

$(LIBFT):
	make -C ./libft/

$(PARSON):
	make -C ./parson/
