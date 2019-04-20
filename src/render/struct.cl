/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.cl                                          :+:      :+:    :+:   */
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
	InfiniteCone = 4,
	Cylinder = 5,
	Cone = 6
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
	float3			position;
	float			intensity;
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
	float		param3;
}						t_figure;

typedef struct			s_ray
{
	float3		o;
	float3		v;
}						t_ray;