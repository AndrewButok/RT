/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/07 18:19:28 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	triangle_init(void)
{
	t_figure figure;

	figure.type = Triangle;
	figure.vector1 = (cl_float3){{0, 0, 0}};
	figure.vector2 = (cl_float3){{0, 0, 0}};
	figure.vector3 = (cl_float3){{0, 0, 0}};
	figure.color = 0xffffff;
	figure.spectacular = 0;
	figure.reflection = 0;
	figure.density = 1;
	figure.transparency = 0;
	return (figure);
}
