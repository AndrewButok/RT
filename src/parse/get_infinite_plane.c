/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infinite_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 15:04:53 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	get_infinite_plane(t_figure *figure, JSON_Object *obj,
		SDL_PixelFormat *pf)
{
	*figure = infinite_plane_init();
	if (!(json_object_has_value_of_type(obj, "normal", JSONArray) &&
		json_object_has_value_of_type(obj, "point", JSONArray)))
		return (false);
	if (!get_vector(json_object_get_array(obj, "normal"), &(figure->vector1)))
		return (false);
	if (!get_vector(json_object_get_array(obj, "point"), &(figure->vector2)))
		return (false);
	if (!get_figure_params(figure, obj, pf))
		return (false);
	figure->vector1 = normalize(figure->vector1);
	return (true);
}
