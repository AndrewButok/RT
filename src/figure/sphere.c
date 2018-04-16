/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 11:58:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/16 11:58:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			get_sqr_solve(double a, double b, double d)
{
	double x1;
	double x2;

	if (d == 0)
		return (-b / 2 * a);
	x1 = (-b + sqrt(d)) / (2 * a);
	x2 = (-b - sqrt(d)) / (2 * a);
	if (x1 <= 1e-11)
		return (x2);
	if (x2 <= 1e-11)
		return (x1);
	return (x1 <= x2 ? x1 : x2);
}

double			check_sphere_intersection(t_ray *ray, t_figure *figure)
{
	t_vector	buf;
	double		a;
	double		b;
	double		c;
	double		d;

	a = vscalar_multiple(ray->v, ray->v);
	buf = vsub(ray->o, figure->center);
	b = 2 * (vscalar_multiple(buf, ray->v));
	c = vscalar_multiple(buf, buf) - (figure->radius * figure->radius);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0)
		return (-1);
	else
		return (get_sqr_solve(a, b, d));
}

t_vector		get_sphere_normale(t_vector p, t_figure *f)
{
	return (vnormalize(vsub(p, f->center)));
}

t_figure		*sphere_init(t_vector center, double r, int color,
		double reflection)
{
	t_figure *new_figure;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = FIGURE_TYPE_SPHERE;
	new_figure->center = center;
	new_figure->radius = r;
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	return (new_figure);
}
