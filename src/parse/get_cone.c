/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/21 22:32:24 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

bool		get_cone(t_figure *figure, JSON_Object *obj, SDL_PixelFormat *pf)
{
	*figure = cone_init();
	if (!(json_object_has_value_of_type(obj, "vertex", JSONArray) &&
		json_object_has_value_of_type(obj, "vector", JSONArray) &&
		json_object_has_value_of_type(obj, "radius", JSONNumber) &&
		json_object_has_value_of_type(obj, "dist1", JSONNumber) &&
		json_object_has_value_of_type(obj, "dist2", JSONNumber)))
		return (false);
	if (!get_vector(json_object_get_array(obj, "vertex"), &(figure->vector1)))
		return (false);
	if (!get_vector(json_object_get_array(obj, "vector"), &(figure->vector2)))
		return (false);
	figure->param1 = (cl_float)json_object_get_number(obj, "radius");
	if (figure->param1 <= 0.01)
		return (false);
	figure->param2 = (cl_float)json_object_get_number(obj, "dist1");
	figure->param3 = (cl_float)json_object_get_number(obj, "dist2");
	if (!get_figure_params(figure, obj, pf))
		return (false);
	figure->vector2 = normalize(figure->vector2);
	if (fabs(figure->param2 - figure->param3) < 0.01f ||
		(figure->param2 < 0 || figure->param3 < 0))
		return (false);
	if (figure->param2 > figure->param3)
		ft_swap(&(figure->param2), &(figure->param3), sizeof(cl_float));
	return (true);
}
