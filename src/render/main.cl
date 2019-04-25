/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				check_intersections(float3 intersection, float3 light,
	  __global t_figure *figures, __global int *params, __global t_figure *cf)
{
	int		i = 0;
	float	k;
	t_ray	ray;

	ray.o = intersection;
	ray.v = light;
	while (i < params[2])
	{
		k = -1.0f;
		k = check_intersection(&ray, &(figures[i]), 0);
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

int				set_brightness(int color, float bright, float reflected)
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

float			trace_reflection(float3 l, float3 normal, float3 view, float3 buf)
{
	float3	h;
	float	d;

	h = view + l;
	d = dot(h, normal);
	if (d > 0)
		return (buf.x * pow(d / length(h), buf.y));
	else
		return (0);
}

int				count_light(__global t_figure *figures, __global t_light *lights,
__global int *params, t_ray *ray, __global t_figure *figure, float3 normal, float len)
{
	float3		intersection = (ray->v * len) + ray->o,
				light;
	float	bright = 0, reflected = 0;
	int		i;

	if (dot(normal, ray->v) >= 0)
		normal = normal * (-1);
	i = 0;
	while (i < params[3])
	{
		if (lights[i].type == Ambient)
			bright += lights[i].intensity;
		if (lights[i].type == Point)
		{
			light = lights[i].position - intersection;
			if (!check_intersections(intersection, light, figures, params, figure))
			{
				if (dot(normal, light) > 0)
					bright += lights[i].intensity * dot(normal, light) /
						length(light);
				if (dot(normal, light) > 0 && figure->reflection > 0)
					reflected += trace_reflection(light, normal, ray->v * (-1),
						(float3)(lights[i].intensity, figure->reflection, 0.0f));
			}
		}
		i++;
	}
	return (set_brightness(figure->color, bright, reflected));
}

int				rt(__global t_figure *figures, __global t_light *lights, t_ray *ray,
		__global int *params)
{
	__private int	index = 0;
	__private int	closest_index;
	float3			normal;
	float3			nbuf;
	float			lbuf;
	float			len = INFINITY;

	while (index < params[2])
	{
		lbuf = check_intersection(ray, &(figures[index]), &nbuf);
		if (lbuf >= 1.0f && lbuf < len)
		{
			len = lbuf;
			normal = nbuf;
			closest_index = index;
		}
		index++;
	}
	if (len == INFINITY)
		return (0);
	else
		return (count_light(figures, lights, params, ray, &(figures[closest_index]), normal, len));
}

__kernel void	do_rt(__global t_figure *figures, __global t_light *lights,
				__global t_ray *cam, __global int *scene, __global int *params)
{
	int				i = get_global_id(get_work_dim() - 1), j, k;
	t_ray			ray;
	float 			step = 1.0f / params[4];
	t_color			buf;
	unsigned int	r = 0,g = 0,b = 0;

	k = 0;
	while (k < params[4])
	{
		j = 0;
		while (j < params[4])
		{
			ray.o = cam->o;
			ray.v.x = (((i % params[0] + (j * step)) / params[0]) * 2.0f - 1.0f) *
		  		(((float)params[0]) / params[1]) * tan(M_PI_F / 360 * 30);
			ray.v.y = (1.0f - 2.0f * ((i / params[0] + (k * step)) / params[1])) *
		  		tan(M_PI_F / 360.0f * 30);
			ray.v.z = 1;
			cam_rotate(&ray, cam->v);
			buf.color = rt(figures, lights, &ray, params);
			r += buf.spectrum.red;
			g += buf.spectrum.green;
			b += buf.spectrum.blue;
			j++;
		}
		k++;
	}
	buf.color = 0;
	r /= params[4] * params[4];
	g /= params[4] * params[4];
	b /= params[4] * params[4];
	buf.spectrum.red = r > 255 ? 255 : r;
	buf.spectrum.green = g > 255 ? 255 : g;
	buf.spectrum.blue = b > 255 ? 255 : b;
	scene[i] = buf.color;
}
