/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void				figure_error(char *error_message, t_figure *figure)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	figure->type = BadFigure;
}

void					get_triangle(t_figure *figure, JSON_Object *obj,
		SDL_PixelFormat *pf)
{
	JSON_Array	*point_array;

	*figure = triangle_init();
	if (json_object_has_value_of_type(obj, "points", JSONArray) &&
json_array_get_count(point_array = json_object_get_array(obj, "points")) == 3)
	{
		figure->vector1 = get_vector(json_array_get_array(point_array, 0),
				figure->vector1);
		figure->vector2 = get_vector(json_array_get_array(point_array, 1),
				figure->vector2);
		figure->vector3 = get_vector(json_array_get_array(point_array, 2),
				figure->vector3);
		if (errno == 107)
		{
			figure_error("Wrong triangle point(s) have been found.", figure);
			return ;
		}
	}
	else
	{
		figure_error("Triangle points not found.", figure);
		return ;
	}
	get_figure_params(figure, obj, pf);
	ft_putendl("\x1b[32mTriangle parsed.");
}
