/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	get_cylinder(t_figure *figure, JSON_Object *obj)
{
	*figure = cylinder_init();
	if (json_object_has_value_of_type(obj, "point", JSONArray))
		figure->vector1 = get_vector(json_object_get_array(obj,"point"),
									 figure->vector1);
	else
		ft_putendl_fd("Cylinder axis point not found. Default applied",
					  STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "vector", JSONArray))
		figure->vector2 = vector_normalize(get_vector(json_object_get_array(obj,
				"vector"), figure->vector2));
	else
		ft_putendl_fd("Cylinder axis vector not found. Default applied",
					  STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "radius", JSONNumber))
		figure->param1 = (cl_float)json_object_get_number(obj, "radius");
	else
		ft_putendl_fd("Cylinder radius not found. Default applied",
					  STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "height", JSONNumber))
		figure->param2 = (cl_float)json_object_get_number(obj, "height");
	else
		ft_putendl_fd("Cylinder height not found. Default applied",
					  STDERR_FILENO);
	get_color_reflection(figure, obj);
	ft_putendl("\x1b[32mCylinder parsed.");
}