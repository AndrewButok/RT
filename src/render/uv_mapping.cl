int	uv_plane_map(const float3 n, const __global t_figure *figure) {
	float3	u;
	float3	v;

	u = (float3){figure->vector1.y, figure->vector1.x, 0};
	if (length(u) == 0)
	{
		u = (float3){figure->vector1.z, figure->vector1.x, 0};
		if (length(u) == 0)
			u = (float3){figure->vector1.y, figure->vector1.z, 0};
	}
	v = cross(figure->vector1, u);
	int2	uv = (int2){dot(u, n * 1000), dot(v, n * 1000)};
	uv %= figure->t_size;
	uv = (int2){uv.x < 0 ? figure->t_size.x - abs(uv.x) : uv.x,
				uv.y < 0 ? figure->t_size.y - abs(uv.y) : uv.y};
	return figure->texture[uv.y * figure->t_size.x + uv.x];
}

int	uv_infinite_cylinder_map(const float3 intersection, __global t_figure *figure)
{
	float3 z = normalize(figure->vector2);
	float3 x = normalize((float3){figure->vector2.y, figure->vector2.x, 0});
	if (length(x) == 0)
	{
		x = normalize((float3){figure->vector2.z, figure->vector2.x, 0});
		if (length(x) == 0)
			x = normalize((float3){figure->vector2.y, figure->vector2.z, 0});
	}
	float3 y = normalize(cross(z, x));
	int v = ((int)dot(z, intersection * 1000)) % figure->t_size.y;
	if (v > 0)
		v = figure->t_size.y - v;
	v = abs(v);
	float u = acos(dot(intersection - (figure->vector1 + figure->vector2 * dot(z, intersection)), x) / (figure->param1 * 2 * M_PI_F));
	u = fabs(u - 2);
	if (isnan(u) || u < 0)
		u = 0;
	else if (u > 1)
		u = 1;
	int s = v * figure->t_size.x + (int)(u * figure->t_size.x);
	return figure->texture[s];
}

int	uv_sphere_map(const float3 n, int *tex, int2 t_size) {
	const int2	uv = { (0.5 + atan2(n.z, n.x) / (2.0 * M_PI_F)) * t_size.x,
						((0.5 - asin(n.y) / M_PI_F) * t_size.y) };
	return tex[uv.y * t_size.x + uv.x];
}