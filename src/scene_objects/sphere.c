/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	sphere_init(cl_float3 center, cl_float radius, cl_int color,
					cl_float reflection)
{
	t_figure figure;

	figure.type = Sphere;
	figure.vector1 = center;
	figure.param1 = radius;
	figure.color = color;
	figure.reflection = reflection;
	return (figure);
}