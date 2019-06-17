/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infinite_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 15:24:21 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	get_infinite_cylinder(t_figure *figure, JSON_Object *obj,
		SDL_PixelFormat *pf)
{
	*figure = infinite_cylinder_init();
	if (!(json_object_has_value_of_type(obj, "point", JSONArray) &&
		json_object_has_value_of_type(obj, "vector", JSONArray) &&
		json_object_has_value_of_type(obj, "radius", JSONNumber)))
		return (false);
	if (!get_vector(json_object_get_array(obj, "point"), &(figure->vector1)))
		return (false);
	if (!get_vector(json_object_get_array(obj, "vector"), &(figure->vector2)))
		return (false);
	figure->param1 = (cl_float)json_object_get_number(obj, "radius");
	if (figure->param1 <= 0)
		return (false);
	if (!get_figure_params(figure, obj, pf))
		return (false);
	figure->vector2 = normalize(figure->vector2);
	return (true);
}
