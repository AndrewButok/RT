/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normales.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (normalize(*intersection - figure->vector1 - figure->vector2 * m));
}

float3		get_infinite_cylinder_normale(float3 *intersection, __global t_figure *figure)
{
	float m;

	m = dot(*intersection - figure->vector1, figure->vector2);
		return (normalize(*intersection - figure->vector1 - figure->vector2 * m));
}

float3		get_cylinder_normale(float3 *intersection, __global t_figure *figure)
{
	float m;

	m = dot(*intersection - figure->vector1, figure->vector2);
	if (m > 1e-3 && m < figure->param2 - 1e-3)
		return (normalize(*intersection - figure->vector1 - figure->vector2 * m));
	return (figure->vector2);
}

float3		get_cone_normale(float3 *intersection, __global t_figure *figure)
{
	float	m;

	m = pow(length(*intersection - figure->vector1), 2) /
			dot(*intersection - figure->vector1, figure->vector2);
	if (m > figure->param2 + 1e-3 && m < figure->param3 - 1e-3)
		return (normalize(*intersection - figure->vector1 - figure->vector2 * m));
	return (figure->vector2);
}

float3 		get_normale(float3 *intersection, __global t_figure *figure)
{
	if (figure->type == Sphere)
		return (get_sphere_normale(intersection, figure));
	else if (figure->type == InfinitePlane)
		return (get_infinite_plane_normale(intersection, figure));
	else if (figure->type == InfiniteCylinder)
		return (get_infinite_cylinder_normale(intersection, figure));
	else if (figure->type == InfiniteCone)
		return (get_infinite_cone_normale(intersection, figure));
	else if (figure->type == Cylinder)
		return (get_cylinder_normale(intersection, figure));
	else if (figure->type == Cone)
		return (get_cone_normale(intersection, figure));
	return (-1);
}
