/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	infinite_cylinder_init(t_ray axis, cl_float radius, cl_int color,
								   cl_float reflection)
{
	t_figure	figure;

	figure.type = InfiniteCylinder;
	figure.vector2 = vector_normalize(axis.v);
	figure.vector1 = axis.o;
	figure.param1 = radius;
	figure.color = color;
	figure.reflection = reflection;
	return (figure);
}