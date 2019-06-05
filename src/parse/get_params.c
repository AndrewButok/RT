/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void		get_rays(t_view *view, JSON_Object *params)
{
	if (json_object_has_value_of_type(params, "antialias", JSONNumber))
		view->antialiasing = (int)json_object_get_number(params, "antialias");
	else
	{
		ft_putendl("Antialias parameter is absent. Default applied");
		view->antialiasing = 1;
		return ;
	}
	if (view->antialiasing > 100 || view->antialiasing < 1)
	{
		ft_putendl("Invalid antialias parameter. Default applied");
		view->antialiasing = 1;
	}
}

static void		get_depth(t_view *view, JSON_Object *params)
{
	if (json_object_has_value_of_type(params, "depth", JSONNumber))
		view->depth = (int)json_object_get_number(params, "depth");
	else
	{
		ft_putendl("Depth parameter is absent. Default applied");
		view->depth = 0;
		return ;
	}
	if (view->depth > 5 || view->depth < 0)
	{
		ft_putendl("Invalid depth parameter. Default applied");
		view->depth = 0;
	}
}

static void		get_wh(t_view *view, JSON_Object *params)
{
	cl_int buf;

	if (json_object_has_value_of_type(params, "width", JSONNumber))
	{
		buf = (cl_int)json_object_get_number(params, "width");
		view->width = buf > 0 && buf <= 5120 ? buf : view->width;
		if (!(buf > 0 && buf <= 5120))
			ft_putendl_fd("Width parameter isn't present or bad."
				"Default applied", STDERR_FILENO);
	}
	else
		ft_putendl_fd("Width parameter isn't present or bad."
				"Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(params, "height", JSONNumber))
	{
		buf = (cl_int)json_object_get_number(params, "height");
		view->height = buf > 0 && buf <= 2880 ? buf : view->height;
		if (!(buf > 0 && buf <= 2880))
			ft_putendl_fd("Height parameter isn't present or bad."
				"Default applied", STDERR_FILENO);
	}
	else
		ft_putendl_fd("Height parameter isn't present or bad."
				"Default applied", STDERR_FILENO);
}

void			get_params(t_view *view, JSON_Object *root)
{
	JSON_Object	*val;

	view->width = 800;
	view->height = 600;
	view->antialiasing = 1;
	view->depth = 0;
	val = json_object_get_object(root, "params");
	if (val != NULL)
	{
		get_wh(view, val);
		get_rays(view, val);
		get_depth(view, val);
		view->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, view->width, view->height, 0);
		view->surface = SDL_GetWindowSurface(view->window);
		view->scene = view->surface->pixels;
	}
	else
		ft_putendl_fd("Default screen params applied.", STDERR_FILENO);
}
