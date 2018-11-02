/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.cl                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float			check_sphere_intersection(t_ray *ray, __global t_figure *figure)
{
	float a;
	float b;
	float c;
	float d;
	float x1, x2;

	a = dot(ray->v, ray->v);
	b = dot(ray->o - figure->vector1, ray->v);
	c = dot(ray->o - figure->vector1, ray->o - figure->vector1) -
		pow(figure->param1, 2.0f);
	d = pow(b, 2.0f) - a * c;
	if (d == 0)
		return ((-b)/a);
	else if (d > 0)
	{
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		if (x1 <= 1e-3)
			return (x2);
		if (x2 <= 1e-3)
			return (x1);
		return (x1 <= x2 ? x1 : x2);
	}
	return (-1);
}

float			check_infinite_plane_intersection(t_ray *ray, __global t_figure *figure)
{
	if (figure->vector1.x != 0 || figure->vector1.y != 0 || figure->vector1.z != 0)
		return (dot(figure->vector1, figure->vector2 - ray->o) /
			dot(figure->vector1, ray->v));
	return (-1);
}

float			check_infinite_cylinder_intersection(t_ray *ray, __global t_figure *figure)
{
	float a;
	float b;
	float c;
	float d;
	float x1, x2;

	a = dot(ray->v, ray->v) - pow(dot(ray->v, figure->vector2), 2);
	b = dot(ray->v, ray->o - figure->vector1) - dot(ray->v, figure->vector2) *
		dot(ray->o - figure->vector1, figure->vector2);
	c = dot(ray->o - figure->vector1, ray->o - figure->vector1) -
		pow(dot(ray->o - figure->vector1, figure->vector2), 2) -
		pow(figure->param1, 2);
	d = pow(b, 2.0f) - a * c;
	if (d == 0)
		return ((-b)/a);
	else if (d > 0)
	{
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		if (x1 <= 1e-3)
			return (x2);
		if (x2 <= 1e-3)
			return (x1);
		return (x1 <= x2 ? x1 : x2);
	}
	return (-1);
}

float	check_cylinder_intersection(t_ray *ray, __global t_figure *figure)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	x1, x2;
	float3	cap_center, intersection;


	a = dot(ray->v, ray->v) - pow(dot(ray->v, figure->vector2), 2);
	b = dot(ray->v, ray->o - figure->vector1) - dot(ray->v, figure->vector2) *
		dot(ray->o - figure->vector1, figure->vector2);
	c = dot(ray->o - figure->vector1, ray->o - figure->vector1) -
		pow(dot(ray->o - figure->vector1, figure->vector2), 2) -
		pow(figure->param1, 2);
	d = pow(b, 2.0f) - a * c;
	if (d >= 0)
	{
		x1 = dot(figure->vector2, figure->vector1 - ray->o) / dot(figure->vector2, ray->v);
		x2 = dot(figure->vector2, figure->vector1 +
				(figure->vector2 * figure->param2) - ray->o) / dot(figure->vector2, ray->v);
		x1 = x1 < x2 ? x1 : x2;
		cap_center = x1 < x2 ? figure->vector1 : (figure->vector1 + (figure->vector2 * figure->param2));
		intersection = ray->v * (x1) + ray->o;
		if (length(cap_center - intersection) <= figure->param1)
			return (x1);
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		a = dot(ray->v, figure->vector2)
			* x1 + dot(ray->o - figure->vector1, figure->vector2);
		b = dot(ray->v, figure->vector2)
			* x2 + dot(ray->o - figure->vector1, figure->vector2);
		if ((x1 > 1e-3 && x2 > 1e-3 && (b > 1e-3 && b < figure->param2)
			&& x1 >= x2) ||
			(x1 <= 1e-3 && x2 > 1e-3 && (b > 1e-3 && b < figure->param2)
			&& x1 < x2))
			return (x2);
		if ((x1 > 1e-3 && x2 > 1e-3 && (a > 1e-3 && a < figure->param2) &&
			x1 < x2)
			|| (x1 > 1e-3 && x2 <= 1e-3) && (a > 1e-3 && a < figure->param2) &&
			x1 >= x2)
			return (x1);
		return (-1);
	}
	else
		return (-1);
}

float 			check_infinite_cone_intersection(t_ray *ray, __global t_figure *figure)
{
	float a, b, c, d, x1, x2;

	a = dot(ray->v, ray->v) - ((1 + pow(figure->param1, 2)) *
		pow(dot(ray->v, figure->vector2), 2));
	b = dot(ray->v, ray->o - figure->vector1) - ((1 + pow(figure->param1, 2)) *
		dot(ray->v, figure->vector2) *
		dot(ray->o - figure->vector1, figure->vector2));
	c = dot(ray->o - figure->vector1, ray->o - figure->vector1) -
		((1 + pow(figure->param1, 2)) *
		pow(dot(ray->o - figure->vector1, figure->vector2), 2));
	d = pow(b, 2.0f) - a * c;
	if (d == 0)
		return ((-b)/a);
	else if (d > 0)
	{
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		if (x1 <= 1e-3)
			return (x2);
		if (x2 <= 1e-3)
			return (x1);
		return (x1 <= x2 ? x1 : x2);
	}
	else
		return (-1);
}

float			check_intersection(t_ray *ray, __global t_figure *figure)
{
	if (figure->type == Sphere)
		return (check_sphere_intersection(ray, figure));
	if (figure->type == InfinitePlane)
		return (check_infinite_plane_intersection(ray, figure));
	if (figure->type == InfiniteCylinder)
		return (check_infinite_cylinder_intersection(ray, figure));
	if (figure->type == InfiniteCone)
		return (check_infinite_cone_intersection(ray, figure));
	if (figure->type == Cylinder)
		return (check_cylinder_intersection(ray, figure));
	return (-1);
}
