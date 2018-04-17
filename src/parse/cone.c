/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 23:35:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/16 23:35:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_cone(JSON_Object *cone, t_view *view)
{
	t_figure	*fcone;

	fcone = cone_init(ray_init((t_vector){0, 0, 0},
			(t_vector){0, -1, 0}), 1, 0xffffff, 0);
	if (json_object_has_value_of_type(cone, "start", JSONArray))
		fcone->center = parse_vector(json_object_get_array(cone,
				"start"), fcone->center);
	else
		ft_putendl_fd("Unknown cone start. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(cone, "vector", JSONArray))
		fcone->axis = vnormalize(parse_vector(json_object_get_array(
				cone, "vector"), fcone->axis));
	else
		ft_putendl_fd("Unknown cone axis vector. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(cone, "radius", JSONNumber))
		fcone->radius = json_object_get_number(cone, "radius");
	else
		ft_putendl_fd("Unknown or invalid cone radius. Default applied",
				STDERR_FILENO);
	parse_color_reflection(cone, fcone);
	add_figure(fcone, view);
}

