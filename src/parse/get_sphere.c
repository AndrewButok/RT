/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/16 21:44:40 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	get_sphere(t_figure *figure, JSON_Object *obj, SDL_PixelFormat *pf)
{
	*figure = sphere_init();
	if (json_object_has_value_of_type(obj, "center", JSONArray))
		figure->vector1 = get_vector(json_object_get_array(obj, "center"),
				figure->vector1);
	else
		ft_putendl_fd("Unknown sphere center. Default applied.", STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "radius", JSONNumber))
		figure->param1 = (cl_float)json_object_get_number(obj, "radius");
	else
		ft_putendl_fd("Unknown sphere radius. Default applied.", STDERR_FILENO);
	get_figure_params(figure, obj, pf);
	ft_putendl("\x1b[32mSphere parsed.");
	return (true);
}
