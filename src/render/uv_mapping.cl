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

int	uv_sphere_map(const float3 n, int *tex, int2 t_size) {
	const int2	uv = { (0.5 + atan2(n.z, n.x) / (2.0 * M_PI_F)) * t_size.x,
						((0.5 - asin(n.y) / M_PI_F) * t_size.y) };
	return tex[uv.y * t_size.x + uv.x];
}