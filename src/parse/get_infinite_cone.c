/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infinite_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_infinite_cone(t_figure *figure, JSON_Object *obj)
{
	*figure = infinite_cone_init();
	if (json_object_has_value_of_type(obj, "vertex", JSONArray))
		figure->vector1 = get_vector(json_object_get_array(obj, "vertex"),
				figure->vector1);
	else
		ft_putendl_fd("Cone vertex not found. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "vector", JSONArray))
		figure->vector2 = vector_normalize(get_vector(json_object_get_array(obj,
				"vector"), figure->vector2));
	else
		ft_putendl_fd("Cone vector not found. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "radius", JSONNumber))
		figure->param1 = (cl_float)json_object_get_number(obj, "radius");
	else
		ft_putendl_fd("Cone radius not found. Default applied", STDERR_FILENO);
	get_color_reflection(figure, obj);
	ft_putendl("\x1b[32mInfinite cone parsed.");
}
