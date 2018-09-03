/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	infinite_cone_init(t_ray axis, cl_float k, cl_int color,
					   cl_float reflection)
{
	t_figure figure;

	figure.vector1 = axis.o;
	figure.vector2 = axis.v;
	figure.param1 = k;
	figure.color = color;
	figure.reflection = reflection;
	figure.type = InfiniteCone;
	return (figure);
}
