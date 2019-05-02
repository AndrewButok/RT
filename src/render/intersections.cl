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
	float	x1, x2;
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
		x1 = x1 < x2 ? x1 : x2;
		cap_center = x1 < x2 ? figure->vector1 : (figure->vector1 + (figure->vector2 * figure->param2));
		intersection = ray->v * (x1) + ray->o;
		if (length(cap_center - intersection) < figure->param1)
		{
			if (normal != 0)
				*normal = figure->vector2;
			return (x1);
		}
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
		{
			if (normal != 0)
				*normal = normalize(ray->o + ray->v * x2 - figure->vector1 -
					figure->vector2 * dot(ray->o + ray->v * x2 - figure->vector1,
						figure->vector2));
			return (x2);
		}
		else if ((x1 > 1e-3 && x2 > 1e-3 && (a > 1e-3 && a < figure->param2) &&
			x1 < x2)
			|| (x1 > 1e-3 && x2 <= 1e-3) && (a > 1e-3 && a < figure->param2) &&
			x1 >= x2)
		{
			if (normal != 0)
				*normal = normalize(ray->o + ray->v * x1 - figure->vector1 -
					figure->vector2 * dot(ray->o + ray->v * x1 - figure->vector1,
						figure->vector2));
			return (x1);
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
	if (d > 0)
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
	float	x1, x2, cap_distance;
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
	if (d > 0)
	{
		x1 = dot(figure->vector2, figure->vector1 +
				(figure->vector2 * figure->param2) - ray->o) / dot(figure->vector2, ray->v);
		x2 = dot(figure->vector2, figure->vector1 +
				(figure->vector2 * figure->param3) - ray->o) / dot(figure->vector2, ray->v);
		if (x1 < x2)
			cap_distance = figure->param2;
		else {
			x1 = x2;
			cap_distance = figure->param3;
		}
		cap_center =  figure->vector1 + (figure->vector2 * cap_distance);
		intersection = ray->v * (x1) + ray->o;
		if (length(cap_center - intersection) < fabs(figure->param1 * cap_distance))
		{
			if (normal != 0)
				*normal = figure->vector2;
			return (x1);
		}
		x1 = ((-b) + sqrt(d)) / a;
		x2 = ((-b) - sqrt(d)) / a;
		a = dot(ray->v, figure->vector2)
			* x1 + dot(ray->o - figure->vector1, figure->vector2);
		b = dot(ray->v, figure->vector2)
			* x2 + dot(ray->o - figure->vector1, figure->vector2);
		if ((x1 > 1e-3 && x2 > 1e-3 && (b > figure->param2 && b < figure->param3)
			&& x1 > x2) ||
			(x1 < 1e-3 && x2 > 1e-3 && (b > figure->param2 && b < figure->param3)
			&& x1 < x2))
		{
			if (normal != 0)
				*normal = normalize(ray->o + ray->v * x2 - figure->vector1 - figure->vector2 *
					(dot(ray->o + ray->v * x2 - figure->vector1, ray->o + ray->v * x2 - figure->vector1) /
						dot(ray->o + ray->v * x2 - figure->vector1, figure->vector2)));
			return (x2);
		}
		if ((x1 > 1e-3 && x2 > 1e-3 && (a > figure->param2 && a < figure->param3) &&
			x1 < x2) ||
			((x1 > 1e-3 && x2 < 1e-3) && (a > figure->param2 && a < figure->param3) &&
			x1 > x2))
		{
			if (normal != 0)
				*normal = normalize(ray->o + ray->v * x1 - figure->vector1 - figure->vector2 *
					(dot(ray->o + ray->v * x1 - figure->vector1, ray->o + ray->v * x1 - figure->vector1) /
						dot(ray->o + ray->v * x1 - figure->vector1, figure->vector2)));
			return (x1);
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

float			select_solution(t_ray *ray, __global t_figure *figure, float3 *normal, float *x1, float *x2, float *x3, float *x4)
{
	float k, m, rv = -1;
	float3 a;
	if (*x1 > 0 && ((*x2 > 0 && *x3 > 0 && *x4 > 0 && *x1 < *x2 && *x1 < *x3 && *x1 < *x4) ||
				   (*x2 > 0 && *x3 > 0 && *x1 < *x2 && *x1 < *x3) ||
				   (*x2 > 0 && *x4 > 0 && *x1 < *x2 && *x1 < *x4) ||
				   (*x3 > 0 && *x4 > 0 && *x1 < *x3 && *x1 < *x4) ||
				   (*x4 > 0 && *x1 < *x4) ||
				   (*x3 > 0 && *x1 < *x3) ||
				   (*x2 > 0 && *x1 < *x2)))
		rv = *x1;
	if (*x2 > 0 && ((*x1 > 0 && *x3 > 0 && *x4 > 0 && *x2 < *x1 && *x2 < *x3 && *x2 < *x4) ||
				   (*x1 > 0 && *x3 > 0 && *x2 < *x1 && *x2 < *x3) ||
				   (*x1 > 0 && *x4 > 0 && *x2 < *x1 && *x2 < *x4) ||
				   (*x3 > 0 && *x4 > 0 && *x2 < *x3 && *x2 < *x4) ||
				   (*x4 > 0 && *x2 < *x4) ||
				   (*x3 > 0 && *x2 < *x3) ||
				   (*x1 > 0 && *x2 < *x1)))
		rv = *x2;
	if (*x3 > 0 && ((*x2 > 0 && *x1 > 0 && *x4 > 0 && *x3 < *x2 && *x3 < *x1 && *x3 < *x4) ||
				   (*x2 > 0 && *x1 > 0 && *x3 < *x2 && *x3 < *x1) ||
				   (*x2 > 0 && *x4 > 0 && *x3 < *x2 && *x3 < *x4) ||
				   (*x1 > 0 && *x4 > 0 && *x3 < *x1 && *x3 < *x4) ||
				   (*x4 > 0 && *x3 < *x4) ||
				   (*x1 > 0 && *x3 < *x1) ||
				   (*x2 > 0 && *x3 < *x2)))
		rv = *x3;
	if (*x4 > 0 && ((*x2 > 0 && *x3 > 0 && *x1 > 0 && *x4 < *x2 && *x4 < *x3 && *x4 < *x1) ||
				   (*x2 > 0 && *x3 > 0 && *x4 < *x2 && *x4 < *x3) ||
				   (*x2 > 0 && *x1 > 0 && *x4 < *x2 && *x4 < *x1) ||
				   (*x3 > 0 && *x1 > 0 && *x4 < *x3 && *x4 < *x1) ||
				   (*x1 > 0 && *x4 < *x1) ||
				   (*x3 > 0 && *x4 < *x3) ||
				   (*x2 > 0 && *x4 < *x2)))
		rv = *x4;
	//TODO: normal of torus;
	if (normal != 0)
	{
		normal = normalize(ray->o + rv * ray->v - a  - (C - a) * m / (R + m))
	}
	return (rv);
}

float			check_torus_intersection(t_ray *ray, __global t_figure *figure, float3 *normal)
{
	float	m, n, o, p, q, r, u, y, w;
	float	a, b, c, d, e;
	float	x1, x2, x3, x4;

	m = dot(ray->v, ray->v);
	n = dot(ray->v, ray->o - figure->vector1);
	o = dot(ray->o - figure->vector1, ray->o - figure->vector1);
	p = dot(ray->v, figure->vector2);
	q = dot(ray->o - figure->vector1, figure->vector2);
	a = pow(m, 2);
	b = 4 * m * n;
	c = 4 * pow(m, 2) + 2 * m * o -
		2 * (pow(figure->param1, 2) + pow(figure->param2, 2)) * m +
		4 * pow(figure->param1, 2) * pow(p, 2);
	d = 4 * n * o - 4 * (pow(figure->param1, 2) + pow(figure->param2, 2)) * n +
		8 * pow(figure->param1, 2) * p * q;
	e = pow(o, 2) - 2 * (pow(figure->param1, 2) + pow(figure->param2, 2)) * o +
		4 * pow(figure->param1, 2) * pow(q, 2) + pow((pow(figure->param1, 2) - pow(figure->param2, 2)), 2);
	m = c / a - (3 * b * b / (8 * a * a));
	n = (b * b * b) / (8 * a * a * a) - (b * c) / (2 * a * a) + d / a;
	o = (-3 * b * b * b * b) / (256 * a * a * a * a) + (c * b * b) / (16 * a * a * a) - (b * d) / (4 * a * a) + e / a;
	// if biquadratic equation
	if (n == 0 && (m * m - 4 * o) > 0)
	{
		if ((-m + sqrt(m * m - 4 * o)) > 0)
		{
			x1 = (-b) / (4 * a) + sqrt((-m + sqrt(m * m - 4 * o)) / 2);
			x2 = (-b) / (4 * a) - sqrt((-m + sqrt(m * m - 4 * o)) / 2);
		}
		else
		{
			x1 = -1;
			x2 = -1;
		}
		if ((-m + sqrt(m * m - 4 * o)) > 0)
		{
			x3 = (-b) / (4 * a) + sqrt((-m - sqrt(m * m - 4 * o)) / 2);
			x4 = (-b) / (4 * a) - sqrt((-m - sqrt(m * m - 4 * o)) / 2);
		}
		else
		{
			x3 = -1;
			x4 = -1;
		}
		return select_solution(ray, figure, normal, &x1, &x2, &x3, &x4);
	}
	p = -(m * m) / 12 - o;
	if (p < 0)
		return (-1);
	q = -(m * m * m) / 108 + (m * o) / 3 - (n * n * n) / 8;
	r = - q / 2 + sqrt((q * q) / 4 + (p * p * p) / 27);
	u = pow(r, 1.0f/3.0f);
	y = - (5 * m) / 6 + u + (u == 0 ? -pow(q, 1.0f/3.0f) : (-p)/ (3 * u));
	if ( m - 2 * y <= 0)
		return (-1);
	w = sqrt(m - 2 * y);
	if ((3 * m + 2 * y + 2 * n / w) < 0)
	{
		x1 = (-b) / (4 * a) + (w + sqrt(-(3 * m + 2 * y + 2 * n / w)) / 2);
		x2 = (-b) / (4 * a) + (w - sqrt(-(3 * m + 2 * y + 2 * n / w)) / 2);
	}
	else
	{
		x1 = -1;
		x2 = -1;
	}
	if ((3 * m + 2 * y + 2 * n / (-w)) < 0)
	{
		x3 = (-b) / (4 * a) + (-w + sqrt(-(3 * m + 2 * y - 2 * n / w)) / 2);
		x4 = (-b) / (4 * a) + (-w - sqrt(-(3 * m + 2 * y - 2 * n / w)) / 2);
	}
	else
	{
		x3 = -1;
		x4 = -1;
	}
	return select_solution(ray, figure, normal, &x1, &x2, &x3, &x4);
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
	else if (figure->type == Torus)
		return (check_torus_intersection(ray, figure, normal));
	return (-1);
}
