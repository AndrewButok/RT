/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 22:58:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/27 22:58:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			check_plane_intersection(t_ray *ray, t_figure *figure)
{
	double r_v;

	r_v = -1;
	if (figure->center.x != 0 || figure->center.y != 0 || figure->center.z != 0)
		r_v = -(figure->radius + vscalar_multiple(ray->o, figure->center)) /
			vscalar_multiple(ray->v, figure->center);
	return (r_v);
}

t_vector		get_plane_normale(t_vector p, t_figure *f)
{
	return (vnormalize(f->center));
	p = (t_vector){0, 0, 0};
}

t_figure		*plane_init(t_vector normale, double d, int color,
		double reflection)
{
	t_figure *new_figure;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = FIGURE_TYPE_PLANE;
	new_figure->center = normale;
	new_figure->radius = d;
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	return (new_figure);
}
