/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/05 14:26:56 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		view_init(t_view **view_ptr, char *filename)
{
	t_view		*view;
	SDL_Event	*event;

	errno = 0;
	view = (t_view*)malloc(sizeof(t_view));
	if (errno != 0)
	{
		perror("View malloc error.");
		return ;
	}
	*view_ptr = view;
	view->figures_count = 0;
	view->lights_count = 0;
	view->figures = NULL;
	view->lights = NULL;
	get_space(view, filename);
	view->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, view->width, view->height, 0);
	view->surface = SDL_GetWindowSurface(view->window);
	view->scene = view->surface->pixels;
	// if (!(view->tex_pxls = rt_sdl_load_textures(view->figures,
					// view->figures_count, view->surface->format)))
		// return ;
	cl_init(view);
	event = (SDL_Event*)malloc(sizeof(SDL_Event));
	event->type = SDL_WINDOWEVENT_EXPOSED;
	SDL_PushEvent(event);
	free(event);
}

int			main(int argc, char **argv)
{
	t_view		*view;
	int			exit_flag;
	SDL_Event	event_iterator;

	if (argc != 2)
		ft_putstr("usage: RT scene_filename\n");
	else
	{
		view_init(&view, argv[1]);
		exit_flag = 0;
		while (exit_flag == 0)
		{
			while (SDL_PollEvent(&event_iterator))
				if ((event_iterator.type == SDL_KEYDOWN &&
				event_iterator.key.keysym.sym == SDLK_ESCAPE) ||
				(event_iterator.type == SDL_WINDOWEVENT &&
				event_iterator.window.event == SDL_WINDOWEVENT_CLOSE))
					exit_flag = 1;
				else if (event_iterator.type == SDL_WINDOWEVENT_EXPOSED)
					SDL_UpdateWindowSurface(view->window);
		}
	}
}
