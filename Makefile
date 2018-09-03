# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abutok <abutok@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/22 16:24:00 by abutok            #+#    #+#              #
#    Updated: 2018/03/22 20:16:18 by abutok           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
PARSON = ./parson/libparson.a
#	C compiler and his default flags
GCC = gcc -Wall -Wextra -Werror
#	Libft linking
LINKLIBFT = -L ./libft -lft
LINKPARSON = -L ./parson -lparson
#	Libs linking
LINKLIB = -framework OpenGL -framework AppKit -framework SDL2 $(LINKLIBFT) $(LINKPARSON) -framework OpenCL
#	Sources directories
SRCDIR = ./src/
COLORDIR = ./src/color/
SCENEDIR = ./src/scene_objects/
LIGHTDIR = ./src/light/
VECTORDIR = ./src/vector/
PARSEDIR = ./src/parse/
#	Source files
SRCFILES = main.c cl.c cl2.c
SCENEFILES = sphere.c infinite_plane.c infinite_cone.c infinite_cylinder.c \
				ray.c light_init.c
VECTORFILES = vector.c
PARSEFILES = ft_hexatoi.c get_space.c  get_sphere.c get_vector.c \
				get_color_reflection.c get_infinite_plane.c \
				get_infinite_cone.c get_infinite_cylinder.c \
				get_light.c get_cam.c get_params.c
#	Header folder
INCLUDE = ./includes
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
#	SDL2 include
SDLINCLUDE = /Library/Frameworks/SDL2.framework/Headers

.NOTPARALLEL = all fclean clean re $(NAME)

all: $(LIBFT) $(PARSON) $(NAME)

$(NAME): $(BINDIR) $(BIN)
	$(GCC) $(LINKLIB) -o $(NAME) $(BIN) -I $(LIBFTINCLUDE) -I $(INCLUDE) \
		-I $(PARSONINCLUDE) -I $(SDLINCLUDE)

$(BINDIR):
	@if [ ! -d "$(BINDIR)" ]; then mkdir $(BINDIR); fi


$(BINDIR)%.o: $(SRCDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) -I $(SDLINCLUDE) $< -o $@

$(BINDIR)%.o: $(PARSEDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) -I $(SDLINCLUDE) $< -o $@

$(BINDIR)%.o: $(SCENEDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) -I $(SDLINCLUDE) $< -o $@

$(BINDIR)%.o: $(VECTORDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) -I $(SDLINCLUDE) $< -o $@

#$(BINDIR)%.o: $(COLORDIR)%.c
#	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) -I $(SDLINCLUDE) $< -o $@

#$(BINDIR)%.o: $(LIGHTDIR)%.c
#	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) -I $(SDLINCLUDE) $< -o $@

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
