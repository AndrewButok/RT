/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:03:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/01 11:03:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			check_cylinder_intersection(t_ray *ray, t_figure *figure)
{
	double a;
	double b;
	double c;
	double d;

	a = vscalar_multiple(ray->v, ray->v) -
			pow(vscalar_multiple(ray->v, figure->axis), 2);
	b = (vscalar_multiple(ray->v, vsub(ray->o, figure->center)) -
			vscalar_multiple(ray->v, figure->axis) *
			vscalar_multiple(vsub(ray->o, figure->center), figure->axis)) * 2;
	c = vscalar_multiple(vsub(ray->o, figure->center),
		vsub(ray->o, figure->center)) -
		pow(vscalar_multiple(vsub(ray->o, figure->center), figure->axis), 2) -
		pow(figure->radius, 2);
	d = pow(b, 2) - 4 * a * c;
	return (get_sqr_solve(a, b, d));
}

t_vector		get_cylinder_normale(t_vector p, t_figure *figure)
{
	double		m;
	t_vector	res;

	m = vscalar_multiple(vsub(p, figure->center), figure->axis);
	res = vsum(figure->center, vk_multiple(figure->axis, m));
	res = vnormalize(vsub(p, res));
	return (res);
}

t_figure		*cylinder_init(t_ray *axis, double radius, int color,
		double reflection)
{
	t_figure *new_figure;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = FIGURE_TYPE_CYLINDER;
	new_figure->center = axis->o;
	new_figure->radius = radius;
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	new_figure->axis = vnormalize(axis->v);
	free(axis);
	return (new_figure);
}
