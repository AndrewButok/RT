/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/18 15:53:22 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool					get_triangle(t_figure *figure, JSON_Object *obj,
		SDL_PixelFormat *pf)
{
	JSON_Array	*point_array;

	*figure = triangle_init();
	if (!(json_object_has_value_of_type(obj, "points", JSONArray)) ||
		json_array_get_count(point_array =
		json_object_get_array(obj, "points")) != 3)
		return (false);
	if (!(get_vector(json_array_get_array(point_array, 0), &figure->vector1) &&
		get_vector(json_array_get_array(point_array, 1), &figure->vector2) &&
		get_vector(json_array_get_array(point_array, 2), &figure->vector3)))
		return (false);
	if (!get_figure_params(figure, obj, pf))
		return (false);
	return (true);
}
