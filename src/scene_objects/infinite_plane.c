/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	infinite_plane_init(cl_float3 normale, cl_float3 point, cl_int color,
							cl_float reflection)
{
	t_figure	figure;

	figure.type = InfinitePlane;
	figure.vector1 = normale;
	figure.vector2 = point;
	figure.color = color;
	figure.reflection = reflection;
	return (figure);
}