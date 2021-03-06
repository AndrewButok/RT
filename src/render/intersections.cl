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

float			check_sphere_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
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
	if (d > 0)
	{
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		x1 = x1 <= 1e-3 ? x2 :
				(x2 <= 1e-3 ? x1 :
				(x1 <= x2 ? x1 : x2));
		if (normal != 0)
			*normal = normalize(ray->o + ray->v * x2 - figure->vector1);
		return (x1);
	}
	return (-1);
}

float			check_infinite_plane_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
{
	if (figure->vector1.x >= 1e-3 || figure->vector1.x <= -1e-3 ||
		figure->vector1.y >= 1e-3 || figure->vector1.y <= -1e-3 ||
		figure->vector1.z >= 1e-3 || figure->vector1.z <= -1e-3)
	{
		if (normal != 0)
			*normal = figure->vector1;
		return (dot(figure->vector1, figure->vector2 - ray->o) /
			dot(figure->vector1, ray->v));
	}
	return (-1);
}

float			check_infinite_cylinder_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
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
	if (d > 0)
	{
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		x1 = x1 <= 1e-3 ? x2 :
				(x2 <= 1e-3 ? x1 :
				(x1 <= x2 ? x1 : x2));
		if (normal != 0)
			*normal = normalize(ray->o + ray->v * x1 - figure->vector1 -
				figure->vector2 * dot(ray->o + ray->v * x1 - figure->vector1,
					figure->vector2));
		return (x1);
	}
	return (-1);
}

float			check_cylinder_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	x1, x2, cd;
	float3	cap_center, intersection;


	a = dot(ray->v, ray->v) - pow(dot(ray->v, figure->vector2), 2);
	b = dot(ray->v, ray->o - figure->vector1) - dot(ray->v, figure->vector2) *
		dot(ray->o - figure->vector1, figure->vector2);
	c = dot(ray->o - figure->vector1, ray->o - figure->vector1) -
		pow(dot(ray->o - figure->vector1, figure->vector2), 2) -
		pow(figure->param1, 2);
	d = pow(b, 2.0f) - a * c;
	if (d > 0)
	{
		x1 = dot(figure->vector2, figure->vector1 - ray->o) / dot(figure->vector2, ray->v);
		x2 = dot(figure->vector2, figure->vector1 +
				(figure->vector2 * figure->param2) - ray->o) / dot(figure->vector2, ray->v);
		cd = INFINITY;
		if (x1 || x2)
		{
			x1 = (x1 < x2 || x2 < 1e-3) && x1 > 1e-3  ? x1 : x2;
			cap_center = (x1 < x2 || x2 < 1e-3) && x1 > 1e-3 ?
				figure->vector1 :
				(figure->vector1 + (figure->vector2 * figure->param2));
			intersection = ray->v * (x1) + ray->o;
			if (length(cap_center - intersection) < figure->param1)
				cd = x1;
		}
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		a = dot(ray->v, figure->vector2)
			* x1 + dot(ray->o - figure->vector1, figure->vector2);
		b = dot(ray->v, figure->vector2)
			* x2 + dot(ray->o - figure->vector1, figure->vector2);
		if (((x1 > 1e-3 && x2 > 1e-3 && x1 >= x2) ||
			(x1 <= 1e-3 && x2 > 1e-3)) && (b > 0 && b < figure->param2))
		{
			if (cd > x2)
			{
				if (normal != 0)
					*normal = normalize(ray->o + ray->v * x2 - figure->vector1 -
						figure->vector2 * dot(ray->o + ray->v * x2 - figure->vector1,
							figure->vector2));
				return (x2);
			}
			if (normal != 0)
				*normal = figure->vector2;
			return (cd);
		}
		else if (((x1 > 1e-3 && x2 > 1e-3 && x1 < x2) ||
			(x1 > 1e-3 && x2 <= 1e-3))
			&& (a > 0 && a < figure->param2))
		{
			if (cd > x1)
			{
				if (normal != 0)
					*normal = normalize(ray->o + ray->v * x1 - figure->vector1 -
						figure->vector2 * dot(ray->o + ray->v * x1 - figure->vector1,
							figure->vector2));
				return (x1);
			}
			if (normal != 0)
				*normal = figure->vector2;
			return (cd);
		}
		else if (cd > 1e-3 && cd != INFINITY)
		{
			if (normal != 0)
				*normal = figure->vector2;
			return (cd);
		}
		return (-1);
	}
	else
		return (-1);
}

float			check_infinite_cone_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
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
	if (d >= 0)
	{
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		x1 = x1 <= 1e-3 ? x2 :
				(x2 <= 1e-3 ? x1 :
				(x1 <= x2 ? x1 : x2));
		if (normal != 0)
			*normal = normalize(ray->o + ray->v * x1 - figure->vector1 - figure->vector2 *
				(dot(ray->o + ray->v * x1 - figure->vector1, ray->o + ray->v * x1 - figure->vector1) /
					dot(ray->o + ray->v * x1 - figure->vector1, figure->vector2)));
		return x1;
	}
	else
		return (-1);
}

float			check_cone_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	x1, x2, cap_distance, cd;
	float3	cap_center, intersection;

	a = dot(ray->v, ray->v) - ((1 + pow(figure->param1, 2)) *
		pow(dot(ray->v, figure->vector2), 2));
	b = dot(ray->v, ray->o - figure->vector1) - ((1 + pow(figure->param1, 2)) *
		dot(ray->v, figure->vector2) *
		dot(ray->o - figure->vector1, figure->vector2));
	c = dot(ray->o - figure->vector1, ray->o - figure->vector1) -
		((1 + pow(figure->param1, 2)) *
		pow(dot(ray->o - figure->vector1, figure->vector2), 2));
	d = pow(b, 2.0f) - a * c;
	if (d >= 0)
	{
		x1 = dot(figure->vector2, figure->vector1 +
				(figure->vector2 * figure->param2) - ray->o) / dot(figure->vector2, ray->v);
		x2 = dot(figure->vector2, figure->vector1 +
				(figure->vector2 * figure->param3) - ray->o) / dot(figure->vector2, ray->v);
		cd = INFINITY;
		if (x1 || x2)
		{
			if ((x1 < x2 || x2 < 1e-3) && x1 > 1e-3)
				cap_distance = figure->param2;
			else
			{
				x1 = x2;
				cap_distance = figure->param3;
			}
			cap_center =  figure->vector1 + (figure->vector2 * cap_distance);
			intersection = ray->v * (x1) + ray->o;
			if (length(cap_center - intersection) < fabs(figure->param1 * cap_distance))
				cd = x1;
		}
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		a = dot(ray->v, figure->vector2)
			* x1 + dot(ray->o - figure->vector1, figure->vector2);
		b = dot(ray->v, figure->vector2)
			* x2 + dot(ray->o - figure->vector1, figure->vector2);
		if (x2 > 1e-3 && ((x1 > 1e-3 && x2 < x1) || x1 < 1e-3 || a < figure->param2 || a > figure->param3) &&
			b > figure->param2 && b < figure->param3)
		{
				if (normal != 0)
					*normal = normalize(ray->o + ray->v * x2 - figure->vector1 - figure->vector2 *
						(dot(ray->o + ray->v * x2 - figure->vector1, ray->o + ray->v * x2 - figure->vector1) /
							dot(ray->o + ray->v * x2 - figure->vector1, figure->vector2)));
				return (x2);
			
		}
		else if (x1 > 1e-3 && ((x2 > 1e-3 && x1 < x2) || x2 < 1e-3 || b < figure->param2 || b > figure->param3) &&
			a > figure->param2 && a < figure->param3)
		{
				if (normal != 0)
					*normal = normalize(ray->o + ray->v * x1 - figure->vector1 - figure->vector2 *
						(dot(ray->o + ray->v * x1 - figure->vector1, ray->o + ray->v * x1 - figure->vector1) /
							dot(ray->o + ray->v * x1 - figure->vector1, figure->vector2)));
				return (x1);
		}
		else if (cd > 1e-3 && cd != INFINITY)
		{
			if (normal != 0)
				*normal = figure->vector2;
			return (cd);
		}
		return (-1);
	}
	else
		return (-1);
}

float			check_triangle_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
{
	float3	n;
	float3	p;
	float	distance;

	n = normalize(cross(figure->vector1 - figure-> vector2, figure->vector3 - figure->vector2));
	if (n.x >= 1e-3 || n.x <= -1e-3 ||
		n.y >= 1e-3 || n.y <= -1e-3 ||
		n.z >= 1e-3 || n.z <= -1e-3)
	{
		if (normal != 0)
			*normal = n;
		distance = dot(n, figure->vector2 - ray->o) / dot(n, ray->v);
		p = ray->o + ray->v * distance;
		if (dot(n, cross(figure->vector2 - figure->vector1, p - figure->vector1)) < 0 &&
			dot(n, cross(figure->vector3 - figure->vector2, p - figure->vector2)) < 0 &&
			dot(n, cross(figure->vector1 - figure->vector3, p - figure->vector3)) < 0)
			return (distance);
		return (-1);
	}
	return (-1);
}

float			check_ellipsoid_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
{
	float	a1, a2, a, b, c, d;
	float	x1, x2;

	a1 = 2.0f * figure->param2 * dot(ray->v, figure->vector2);
	a2 = figure->param1 * figure->param1 + 2.0f * figure->param2 * dot(ray->o - figure->vector1, figure->vector2) - figure->param2;
	a = pow(2.0f * figure->param1, 2.0f) * dot(ray->v, ray->v) - a1 * a1;
	b = pow(2.0f * figure->param1, 2.0f) * dot(ray->v, ray->o - figure->vector1) - a1 * a2;
	c = pow(2.0f * figure->param1, 2.0f) * dot(ray->o - figure->vector1, ray->o - figure->vector1) - a2 * a2;
	d = pow(b, 2.0f) - a * c;
	if (d > 0)
	{
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		x1 = x1 < 1e-3 ? x2 :
	 		(x2 < 1e-3 ? x1 :
	 		(x1 < x2 ? x1 : x2));
		if (normal != 0)
		{
			float3 r, cmid;

			cmid = figure->vector1 + figure->vector2 * (figure->param2 / 2.0f);
			r = (ray->o + ray->v * x1) - cmid;
			*normal = normalize(r - (figure->vector2 * (1.0f - (b * b) / (c * a)) * dot(r, figure->vector2)));
		}
		return (x1);
	}
	return (-1);
}

float			check_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
{
	if (figure->type == Sphere)
		return (check_sphere_intersection(ray, figure, normal));
	else if (figure->type == InfinitePlane)
		return (check_infinite_plane_intersection(ray, figure, normal));
	else if (figure->type == InfiniteCylinder)
		return (check_infinite_cylinder_intersection(ray, figure, normal));
	else if (figure->type == InfiniteCone)
		return (check_infinite_cone_intersection(ray, figure, normal));
	else if (figure->type == Cylinder)
		return (check_cylinder_intersection(ray, figure, normal));
	else if (figure->type == Cone)
		return (check_cone_intersection(ray, figure, normal));
	else if (figure->type == Triangle)
		return (check_triangle_intersection(ray, figure, normal));
	else if (figure->type == Ellipsoid)
		return (check_ellipsoid_intersection(ray, figure, normal));
	return (-1);
}
