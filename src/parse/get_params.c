/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 01:51:33 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static bool		get_rays(t_view *view, JSON_Object *params)
{
	if (!json_object_has_value_of_type(params, "antialias", JSONNumber))
		return (false);
	view->antialiasing = (int)json_object_get_number(params, "antialias");
	if (view->antialiasing <= 0 || view->antialiasing > 5)
		return (false);
	return (true);
}

static bool		get_depth(t_view *view, JSON_Object *params)
{
	if (!json_object_has_value_of_type(params, "depth", JSONNumber))
		return (false);
	view->depth = (int)json_object_get_number(params, "depth");
	if (view->depth < 0 || view->depth >= 4)
		return (false);
	return (true);
}

static bool		get_wh(t_view *view, JSON_Object *params)
{
	cl_int buf;

	if (!(json_object_has_value_of_type(params, "width", JSONNumber) &&
		json_object_has_value_of_type(params, "height", JSONNumber)))
		return (false);
	view->width = (cl_int)json_object_get_number(params, "width");
	if (view->width < 320 || view->width >= 5120)
		return (false);
	view->height = (cl_int)json_object_get_number(params, "height");
	if (view->height < 240 || view->height >= 2880)
		return (false);
	return (true);
}

static bool		get_filter(t_view *view, JSON_Object *params)
{
	if (!(json_object_has_value_of_type(params, "filter", JSONString) &&
		check_hex(json_object_get_string(params, "filter"))))
		return (false);
	view->filter = ft_hexatoi(json_object_get_string(params, "filter"));
	return (true);
}

bool			get_params(t_view *view, JSON_Object *root)
{
	JSON_Object	*val;

	if (root == NULL || !json_object_has_value_of_type(root, "params", JSONObject))
		return (false);
	val = json_object_get_object(root, "params");
	if (val == NULL || !(get_filter(view, val)
		&& get_wh(view, val) && get_rays(view, val)
		&& get_depth(view, val)))
		return (false);
	view->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, view->width, view->height, 0);
	view->surface = SDL_GetWindowSurface(view->window);
	view->scene = view->surface->pixels;
	return (true);
}
