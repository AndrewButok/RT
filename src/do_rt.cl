/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rt.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum			e_figure
{
	BadFigure = 0,
	Sphere = 1,
	InfinitePlane = 2,
	InfiniteCylinder = 3,
	InfiniteCone = 4
};

enum			e_light
{
	BadLight = -1,
	Ambient = 0,
	Point = 1
};

typedef union			u_color
{
	int				color;
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	}				spectrum;
}						t_color;

typedef struct			s_light
{
	enum e_light	type;
	float3		position;
	float		intensity;
}						t_light;

typedef struct 			s_figure
{
	float		reflection;
	int			color;
	enum e_figure 	type;
	float3		vector1;
	float3		vector2;
	float		param1;
	float		param2;
}						t_figure;

typedef struct			s_ray
{
	float3		o;
	float3		v;
}						t_ray;

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
	else
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
	return (-1);
}

float3		get_sphere_normale(float3 *intersection, __global t_figure *figure)
{
	return (normalize(*intersection - figure->vector1));
}

float3		get_infinite_plane_normale(float3 *intesection, __global t_figure *figure)
{
	return (figure->vector1);
}

float3		get_infinite_cone_normale(float3 *intersection, __global t_figure *figure)
{
	float	m;

	m = pow(length(*intersection - figure->vector1), 2) /
			dot(*intersection - figure->vector1, figure->vector2);
	return (normalize(*intersection - figure->vector1 - (figure->vector2 * m)));
}

float3		get_infinite_cylinder_normale(float3 *intersection, __global t_figure *figure)
{
	float m;

	m = dot(*intersection - figure->vector1, figure->vector2);
	return (normalize(*intersection - (figure->vector1 + (figure->vector2 * m))));
}

float3 		get_normale(float3 *intersection, __global t_figure *figure)
{
	if (figure->type == Sphere)
		return (get_sphere_normale(intersection, figure));
	if (figure->type == InfinitePlane)
		return (get_infinite_plane_normale(intersection, figure));
	if (figure->type == InfiniteCylinder)
		return (get_infinite_cylinder_normale(intersection, figure));
	if (figure->type == InfiniteCone)
		return (get_infinite_cone_normale(intersection, figure));
	return (-1);
}

int			check_intersections(float3 intersection, float3 light,
		__global t_figure *figures, __global int *params)
{
	int		i = 0;
	float	k;
	t_ray	ray;

	ray.o = intersection;
	ray.v = light;
	while (i < params[4])
	{
		k = check_intersection(&ray, &(figures[i]));
		if (k < 1 && k >= 1e-3)
			return (1);
		i++;
	}
	return (0);
}

int				set_spectrum_brightness(int val, float bright,
												  float reflected)
{
	return ((int)(val * bright + (255 - val) * reflected));
}

unsigned char	limit_spectrum(int d, int min, int max)
{
	d = d > max ? max : d;
	d = d < min ? min : d;
	return ((unsigned char)d);
}
int			set_brightness(int color, float bright, float reflected)
{
	t_color coloru;

	bright += reflected;
	bright = bright >= 1 ? 1 : bright;
	reflected = reflected >= 1 ? 1 : reflected;
	coloru.color = color;
	coloru.spectrum.red = limit_spectrum(
			set_spectrum_brightness(coloru.spectrum.red, bright,
									reflected), 0, 255);
	coloru.spectrum.green = limit_spectrum(
			set_spectrum_brightness(coloru.spectrum.green, bright,
									reflected), 0, 255);
	coloru.spectrum.blue = limit_spectrum(
			set_spectrum_brightness(coloru.spectrum.blue, bright,
									reflected), 0, 255);
	return (coloru.color);
}
float		trace_reflection(float3 l, float3 normale, float3 view, float3 buf)
{
	float3	h;
	float	d;

	h = view + l;
	d = dot(h, normale);
	if (d > 0)
		return (buf.x * pow(d / length(h), buf.y));
	else
		return (0);
}

int			count_light(__global t_figure *figures, __global t_light *lights,
		__global int *params, t_ray *ray, __global t_figure *figure, float len)
{
	float3	intersection = (ray->v * len) + ray->o,
			normale = get_normale(&intersection, figure),
			light;
	float	bright = 0, reflected = 0;
	int		i;

	if (dot(normale, ray->v) >= 0)
		normale = normale * (-1);
	i = 0;
	while (i < params[5])
	{
		if (lights[i].type == Ambient)
			bright += lights[i].intensity;
		if (lights[i].type == Point)
		{
			light = lights[i].position - intersection;
			if (!check_intersections(intersection, light, figures, params))
			{
				if (dot(normale, light) > 0)
					bright += lights[i].intensity * dot(normale, light) /
							length(light);
				if (dot(normale, light) > 0 && figure->reflection > 0)
					reflected += trace_reflection(light, normale, ray->v * (-1),
						(float3)(lights[i].intensity, figure->reflection, 0.0f));
			}
		}
		i++;
	}
	return (set_brightness(figure->color, bright, reflected));
}

int			rt(__global t_figure *figures, __global t_light *lights, t_ray *ray,
		__global int *params)
{
	__private int	index = 0;
	__private int	closest_index;
	float			lbuf;
	float			len = INFINITY;


	while (index < params[4])
	{
		lbuf = check_intersection(ray, &(figures[index]));
		if (lbuf >= 1.0f && lbuf < len)
		{
			len = lbuf;
			closest_index = index;
		}
		index++;
	}
	if (len == INFINITY)
		return (0);
	else
		return (count_light(figures, lights, params, ray, &(figures[closest_index]), len));
}

void	cam_rotate(t_ray *ray, float3 rotate_v)
{
	float n1, n2;

	rotate_v *= (M_PI_F / 180.0f);
	if (rotate_v.x != 0)
	{
		n1 = ray->v.y * cos(rotate_v.x) + ray->v.z * sin(rotate_v.x);
		n2 = ray->v.z * cos(rotate_v.x) - ray->v.y * sin(rotate_v.x);
		ray->v.y = n1;
		ray->v.z = n2;
	}
	if (rotate_v.y != 0)
	{
		n1 = ray->v.x * cos(rotate_v.y) + ray->v.z * sin(rotate_v.y);
		n1 = ray->v.z * cos(rotate_v.y) - ray->v.x * sin(rotate_v.y);
		ray->v.x = n1;
		ray->v.z = n2;
	}
	if (rotate_v.z != 0)
	{
		n1 = ray->v.x * cos(rotate_v.z) + ray->v.y * sin(rotate_v.z);
		n2 = ray->v.y * cos(rotate_v.z) - ray->v.x * sin(rotate_v.z);
		ray->v.x = n1;
		ray->v.y = n2;
	}
}

__kernel void do_rt(__global t_figure *figures, __global t_light *lights,
		__global t_ray *cam, __global int *scene, __global int *params)
{
	int		i = get_global_id(get_work_dim() - 1);
	t_ray	ray;

	ray.o = cam->o;
	ray.v.x = (((i % params[0] + 0.5f) / params[0]) * 2.0f - 1.0f) *
			(((float)params[0]) / params[1]) *
			tan(M_PI_F / 360 * params[2]);
	ray.v.y = (1.0f - 2.0f * ((i / params[0] + 0.5f) / params[1])) *
						 tan(M_PI_F / 360.0f * params[3]);
	ray.v.z = 1;
	cam_rotate(&ray, cam->v);
	scene[i] = rt(figures, lights, &ray, params);
}