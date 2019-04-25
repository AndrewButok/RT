/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elipsoid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_ellipsoid_radii(t_figure *figure, JSON_Object *obj)
{
	if (json_object_has_value_of_type(obj, "radius1", JSONNumber))
		figure->param1 += json_object_get_number(obj, "radius1");
	else
		ft_putendl_fd("Ellipsoid first radius not found. Default applied",
					STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "radius2", JSONNumber))
		figure->param1 += json_object_get_number(obj, "radius2");
	else
		ft_putendl_fd("Ellipsoid second radius not found. Default applied",
					STDERR_FILENO);
}

void		get_ellipsoid(t_figure *figure, JSON_Object *obj)
{
	*figure = ellipsoid_init();
	if (json_object_has_value_of_type(obj, "center1", JSONArray))
		figure->vector1 = get_vector(json_object_get_array(obj, "center1"),
				figure->vector1);
	else
		ft_putendl_fd("Ellipsoid first center not found. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "center2", JSONArray))
	{
		figure->vector2 = get_vector(json_object_get_array(obj, "center2"),
				figure->vector2);
		figure->param2 = vector_length(vector_sub(figure->vector2,
				figure->vector1));
		figure->vector2 = vector_normalize(vector_sub(figure->vector2,
				figure->vector1));
	}
	else
		ft_putendl_fd("Ellipsoid second center not found. Default applied",
					STDERR_FILENO);
	get_ellipsoid_radii(figure, obj);
	get_color_reflection(figure, obj);
	ft_putendl("\x1b[32mEllipsoid parsed.");
}
