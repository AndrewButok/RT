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

inline __attribute__((always_inline)) int set_spectrum_brightness(int val, float bright,
										   float reflected)
{
	return ((int)(val * bright + (255 - val) * reflected));
}

inline __attribute__((always_inline)) unsigned char	limit_spectrum(int d, int min, int max)
{
	d = d > max ? max : d;
	d = d < min ? min : d;
	return ((unsigned char)d);
}

inline __attribute__((always_inline)) int				set_brightness(int color, float bright, float reflected)
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

inline __attribute__((always_inline)) float			trace_spectacular(float3 l, float3 normal, float3 view, float3 buf)
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
				if (dot(normal, light) > 0 && figure->spectacular > 0)
					reflected += trace_spectacular(light, normal, ray->v * (-1),
						(float3)(lights[i].intensity, figure->spectacular, 0.0f));
			}
		}
		i++;
	}
	return (set_brightness(figure->color, bright, reflected));
}

inline __attribute__((always_inline)) float3	ft_reflect_ray(float3 r, float3 normal)
{
	return (2 * normal * dot(normal, r) - r);
}

inline __attribute__((always_inline)) int ft_change_color(t_color color, float scale)
{
	color.spectrum.red = ((color.spectrum.red * scale) > 255) ? 255 : color.spectrum.red * scale;
	color.spectrum.green = ((color.spectrum.green * scale) > 255) ? 255 : color.spectrum.green * scale;
	color.spectrum.blue = ((color.spectrum.blue * scale) > 255) ? 255 : color.spectrum.blue * scale;
	return (color.color);
}

inline __attribute__((always_inline)) int ft_add_color(t_color color1, t_color color2)
{
	t_color new;

	new.spectrum.red = ((color1.spectrum.red + color2.spectrum.red) > 255) ? 255 : color1.spectrum.red + color2.spectrum.red;
	new.spectrum.green = ((color1.spectrum.green + color2.spectrum.green) > 255) ? 255 : color1.spectrum.green + color2.spectrum.green;
	new.spectrum.blue = ((color1.spectrum.blue + color2.spectrum.blue) > 255) ? 255 : color1.spectrum.blue + color2.spectrum.blue;
	return (new.color);
}

int				rt(__global t_figure *figures, __global t_light *lights, t_ray *ray,
		__global int *params, float t_min, float t_max, int depth)
{
	int				index = -1;
	int				closest_index;
	float3			normal;
	float3			nbuf;
	float			t = DBL_MAX;
	t_color			local_color;
	t_color			reflected_color;
	t_ray			reflect_ray;

	while (++index < params[2])
	{
		t = check_intersection(ray, &(figures[index]), &nbuf);
		if (t >= t_min && t < t_max)
		{
			t_max = t;//////////////////// should change
			normal = nbuf;
			closest_index = index;
		}
	}
	if (t == DBL_MAX)
		return (0);
	local_color.color = count_light(figures, lights, params, ray, &(figures[closest_index]), normal, t_max);

	if (depth < 0 || figures[closest_index].reflection < 0.0)
		return (local_color.color);
	reflect_ray.v = ft_reflect_ray(-ray->v, normal);
	reflect_ray.o = (ray->o + (ray->v * t_max));
	reflected_color.color = rt(figures, lights, &reflect_ray, params, 0.001, DBL_MAX, depth - 1);
	
	local_color.color = ft_change_color(local_color, (1.0 - figures[closest_index].reflection));

	reflected_color.color = ft_change_color(reflected_color, (figures[closest_index].reflection));

	local_color.color = ft_add_color(local_color, reflected_color);

	return (local_color.color);
}

__kernel void	do_rt(__global t_figure *figures, __global t_light *lights,
				__global t_ray *cam, __global int *scene, __global int *params)
{
	int				i = get_global_id(get_work_dim() - 1), j, k;
	t_ray			ray;
	float 			step = 1.0f / params[4];
	t_color			buf;
	unsigned int	r = 0,g = 0,b = 0;
	int				depth = params[5];
	float			t_max = DBL_MAX;

	k = 0;
	while (k < params[4])
	{
		j = 0;
		while (j < params[4])
		{
			ray.o = cam->o;
			ray.v.x = (2 * tan (M_PI_F / 360.0f * 60) *
					(i % params[0] - params[0] / 2 + j * step)) / params[0];
			ray.v.y = (2 * tan (-M_PI_F / 360.0f * 60) *
					(i / params[0] - params[1] / 2 + k * step)) / params[0];
			ray.v.z = 1;
			cam_rotate(&ray, cam->v);
			t_max = DBL_MAX;
			buf.color = rt(figures, lights, &ray, params, 0.001, t_max, depth - 1);
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
