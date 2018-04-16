/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:33:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/04 14:33:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			check_cone_intersection(t_ray *ray, t_figure *figure)
{
	double a;
	double b;
	double c;
	double d;

	a = vscalar_multiple(ray->v, ray->v) -
			((1 + pow(figure->radius, 2)) *
			(pow(vscalar_multiple(ray->v, figure->axis), 2)));
	b = 2 * (vscalar_multiple(ray->v, vsub(ray->o, figure->center)) -
			((1 + pow(figure->radius, 2)) *
			vscalar_multiple(ray->v, figure->axis) *
			vscalar_multiple(vsub(ray->o, figure->center), figure->axis)));
	c = vscalar_multiple(vsub(ray->o, figure->center),
			vsub(ray->o, figure->center)) -
			((1 + pow(figure->radius, 2)) *
			(pow(vscalar_multiple(vsub(ray->o, figure->center),
					figure->axis), 2)));
	d = pow(b, 2) - 4 * a * c;
	return (get_sqr_solve(a, b, d));
}

t_vector		get_cone_normale(t_vector p, t_figure *figure)
{
	double		m;
	t_vector	res;

	m = pow(vlen(vsub(p, figure->center)), 2) / vscalar_multiple(vsub(p,
			figure->center), figure->axis);
	res = vsum(figure->center, vk_multiple(figure->axis, m));
	res = vnormalize(vsub(p, res));
	return (res);
}

t_figure		*cone_init(t_ray *axis, double k, int color,
		double reflection)
{
	t_figure *new_figure;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = FIGURE_TYPE_CONE;
	new_figure->center = axis->o;
	new_figure->radius = k;
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	new_figure->axis = vnormalize(axis->v);
	free(axis);
	return (new_figure);
}
