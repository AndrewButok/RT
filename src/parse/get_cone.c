/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void	get_cone_distances(t_figure *figure, JSON_Object *obj)
{
	if (json_object_has_value_of_type(obj, "dist1", JSONNumber))
		figure->param2 = (cl_float)json_object_get_number(obj, "dist1");
	else
		ft_putendl_fd("Cone distance from top cap to vertex not found.",
				STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "dist2", JSONNumber))
		figure->param3 = (cl_float)json_object_get_number(obj, "dist2");
	else
		ft_putendl_fd("Cone distance from bottom cap to vertex not found.",
				STDERR_FILENO);
	if (figure->param2 > figure->param3)
		ft_swap(&(figure->param2), &(figure->param3), sizeof(cl_float));
}

void		get_cone(t_figure *figure, JSON_Object *obj)
{
	*figure = cone_init();
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
	get_cone_distances(figure, obj);
	get_color_reflection(figure, obj);
	ft_putendl("\x1b[32mCone parsed.");
}
