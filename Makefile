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
#	C compiler and his default flags
GCC = gcc -Wall -Wextra -Werror
#	Libft linking
LINKLIBFT = -L ./libft -lft
LINKPARSON = -L ./parson -lparson
#	Libs linking
LINKLIB = -framework OpenGL -framework AppKit -lmlx $(LINKLIBFT) $(LINKPARSON)
#	Sources directories
SRCDIR = ./src/
COLORDIR = ./src/color/
FIGUREDIR = ./src/figure/
LIGHTDIR = ./src/light/
VECTORDIR = ./src/vector/
PARSEDIR = ./src/parse/
#	Source files
SRCFILES = do_rt.c main.c space.c
COLORFILES = color.c
FIGUREFILES = figure.c sphere.c plane.c cylinder.c cone.c triangle.c
LIGHTFILES = light.c
VECTORFILES = vector.c vector2.c rotate.c
PARSEFILES = cam.c cone.c cylinder.c error.c ft_hexatoi.c light.c parse.c plane.c \
			sphere.c triangle.c
#	Header folder
INCLUDE = ./includes
#	Binaries folder
BINDIR = ./obj/
#	Binaries list
BIN = $(addprefix $(BINDIR), $(SRCFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(COLORFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(FIGUREFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(LIGHTFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(VECTORFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(PARSEFILES:.c=.o))
#	Libft
LIBFT = ./libft/libft.a
#	Libft header
LIBFTINCLUDE = ./libft/includes
#	Parson header
PARSONINCLUDE = ./parson

.NOTPARALLEL = all fclean clean re $(NAME)

all: $(LIBFT) $(PARSON) $(NAME)

$(NAME): $(BINDIR) $(BIN)
	$(GCC) $(LINKLIB) -o $(NAME) $(BIN) -I $(LIBFTINCLUDE) -I $(INCLUDE) -I $(PARSONINCLUDE)

$(BINDIR):
	@if [ ! -d "$(BINDIR)" ]; then mkdir $(BINDIR); fi

$(BINDIR)%.o: $(PARSEDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(SRCDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(COLORDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(FIGUREDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(LIGHTDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(VECTORDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

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
