/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 11:58:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/16 11:58:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "rtv1.h"

t_ray		*ray_init(t_vector origin, t_vector vector)
{
	t_ray *ray;

	ray = (t_ray*)malloc(sizeof(t_ray));
	ray->o = origin;
	ray->v = vector;
	return (ray);
}

t_vector	get_normale(t_vector ray, t_figure *f)
{
	if (f->type == FIGURE_TYPE_SPHERE)
		return (get_sphere_normale(ray, f));
	else if (f->type == FIGURE_TYPE_PLANE)
		return (get_plane_normale(ray, f));
	else if (f->type == FIGURE_TYPE_CYLINDER)
		return (get_cylinder_normale(ray, f));
	else if (f->type == FIGURE_TYPE_CONE)
		return (get_cone_normale(ray, f));
	return ((t_vector){0, 0, 0});
}

t_vector	get_intersection(t_ray *ray, double k)
{
	return (vsum(vk_multiple(ray->v, k), ray->o));
}

double		check_intersection(t_ray *ray, t_figure *figure)
{
	if (figure->type == FIGURE_TYPE_SPHERE)
		return (check_sphere_intersection(ray, figure));
	else if (figure->type == FIGURE_TYPE_PLANE)
		return (check_plane_intersection(ray, figure));
	else if (figure->type == FIGURE_TYPE_CYLINDER)
		return (check_cylinder_intersection(ray, figure));
	else if (figure->type == FIGURE_TYPE_CONE)
		return (check_cone_intersection(ray, figure));
	return (-1);
}

int			check_intersections(t_ray *ray, t_figure *figures)
{
	t_figure	*it;
	double		k;

	it = figures;
	while (it != NULL)
	{
		k = check_intersection(ray, it);
		if (k < 1 && k >= 1e-11)
			return (1);
		it = it->next;
	}
	return (0);
}
