/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 12:22:52 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	get_sphere(t_figure *figure, JSON_Object *obj, SDL_PixelFormat *pf)
{
	*figure = sphere_init();
	if (!(json_object_has_value_of_type(obj, "center", JSONArray) &&
		json_object_has_value_of_type(obj, "radius", JSONNumber)))
		return (false);
	if (!get_vector(json_object_get_array(obj, "center"), &(figure->vector1)))
		return (false);
	if ((figure->param1 =
		(cl_float)json_object_get_number(obj, "radius")) <= 0)
		return (false);
	if (!get_figure_params(figure, obj, pf))
		return (false);
	return (true);
}
