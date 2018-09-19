/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infinite_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_infinite_plane(t_figure *figure, JSON_Object *obj)
{
	*figure = infinite_plane_init();
	if (json_object_has_value_of_type(obj, "normale", JSONArray))
		figure->vector1 = vector_normalize(get_vector(json_object_get_array(obj, "normale"),
				figure->vector1));
	else
		ft_putendl_fd("Plane normale not found. Default applied.",
					  STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "point", JSONArray))
		figure->vector2 = get_vector(json_object_get_array(obj, "point"),
									 figure->vector2);
	else
		ft_putendl_fd("Plane point not found. Default applied.",
					  STDERR_FILENO);
	get_color_reflection(figure, obj);
	ft_putendl("\x1b[32mInfinite plane parsed.");
}
