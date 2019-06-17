/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 18:43:57 by abutok           ###   ########.fr       */
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
	if (!get_space(view, filename))
	{
		ft_putendl_fd("Parse error. Check your file", STDERR_FILENO);
		exit(-1);
	}
	cl_init(view);
	event = (SDL_Event*)malloc(sizeof(SDL_Event));
	event->type = SDL_WINDOWEVENT_EXPOSED;
	SDL_PushEvent(event);
	free(event);
}

void		make_screenshot(t_view *view)
{
	SDL_Surface *screenshot;

	SDL_LockSurface(view->surface);
	screenshot = SDL_CreateRGBSurface(0, view->width,
		view->height, 32, 0, 0, 0, 0);
	ft_memcpy(screenshot->pixels, view->surface->pixels,
		screenshot->h * screenshot->pitch);
	SDL_SaveBMP(screenshot, "screenshot.bmp");
	SDL_UnlockSurface(view->surface);
	SDL_FreeSurface(screenshot);
}

void		event_manager(t_view *view, SDL_Event *event, int *exit)
{
	if ((event->type == SDL_KEYDOWN &&
				event->key.keysym.sym == SDLK_ESCAPE) ||
				(event->type == SDL_WINDOWEVENT &&
				event->window.event == SDL_WINDOWEVENT_CLOSE))
		*exit = 1;
	else if (event->type == SDL_WINDOWEVENT_EXPOSED)
		SDL_UpdateWindowSurface(view->window);
	else if (event->type == SDL_KEYDOWN &&
				event->key.keysym.sym == SDLK_p)
		make_screenshot(view);
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
				event_manager(view, &event_iterator, &exit_flag);
		}
	}
}
