/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_sphere(t_figure *figure, JSON_Object *obj)
{
	*figure = sphere_init();
	if (json_object_has_value_of_type(obj, "center", JSONArray))
		figure->vector1 = get_vector(json_object_get_array(obj, "center"),
				figure->vector1);
	else
		ft_putendl_fd("Unknown sphere center. Default applied.", STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "radius", JSONNumber))
		figure->param1 = (cl_float)json_object_get_number(obj, "radius");
	else
		ft_putendl_fd("Unknown sphere radius. Default applied.", STDERR_FILENO);
	get_color_reflection(figure,obj);
	ft_putendl("\x1b[32mSphere parsed.");
}
