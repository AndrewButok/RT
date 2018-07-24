/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 01:11:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/14 15:50:41 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	view_init(t_view **view_ptr, char *filename)
{
	t_view		*view;

	errno = 0;
	view = (t_view*)malloc(sizeof(t_view));
	if (errno != 0)
	{
		perror("View malloc error");
	}
	*view_ptr = view;
	space_init(filename, view);
	view->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	view->surface = SDL_GetWindowSurface(view->window);
	view->scene = (int*)view->surface->pixels;
	do_rt(view);
	SDL_UpdateWindowSurface(view->window);
}

int			do_keyboard(int key, t_view *view)
{
	if (key == SDLK_ESCAPE)
		exit_x(view);
	return (1);
}

int			exit_x(t_view *view)
{
	exit(1);
	view = NULL;
	return (0);
}

int			main(int argc, char **argv)
{
	t_view		*view;
	SDL_Event	event;
	char		h;

	if (argc != 2)
	{
		ft_putstr("usage: RT scene_filename\n");
		return (0);
	}
	h = 0;
	view_init(&view, argv[1]);
	while (1)
    {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_KEYDOWN)
                h = 1;
            else if (event.type == SDL_WINDOWEVENT &&
					 event.window.event == SDL_WINDOWEVENT_CLOSE)
            	h = 1;
		if (h)
           	break;
    }
}
