/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:55:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/17 14:08:31 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_plane(JSON_Object *plane, t_view *view)
{
	t_figure	*fplane;

	fplane = plane_init((t_vector){0, 0, 0}, 1, 0xffffff, 0);
	if (json_object_has_value_of_type(plane, "normale", JSONArray))
		fplane->center = parse_vector(json_object_get_array(plane,
				"normale"), fplane->center);
	else
		ft_putendl_fd("Unknown plane normale. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(plane, "d", JSONNumber))
		fplane->radius = json_object_get_number(plane, "d");
	else
		ft_putendl_fd("Unknown or invalid plane d parameter. Default applied",
				STDERR_FILENO);
	parse_color_reflection(plane, fplane);
	add_figure(fplane, view);
}
