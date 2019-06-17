/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ellipsoid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 18:31:53 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool		get_ellipsoid(t_figure *figure, JSON_Object *obj,
		SDL_PixelFormat *pf)
{
	*figure = ellipsoid_init();
	if (!(json_object_has_value_of_type(obj, "center1", JSONArray) &&
		json_object_has_value_of_type(obj, "center2", JSONArray) &&
		json_object_has_value_of_type(obj, "radius", JSONNumber)))
		return (false);
	if (!get_vector(json_object_get_array(obj, "center1"), &figure->vector1))
		return (false);
	if (!get_vector(json_object_get_array(obj, "center2"), &figure->vector2))
		return (false);
	figure->param1 = json_object_get_number(obj, "radius");
	figure->param2 = length(sub(figure->vector2, figure->vector1));
	figure->vector2 = normalize(sub(figure->vector2, figure->vector1));
	if (!get_figure_params(figure, obj, pf))
		return (false);
	return (true);
}
