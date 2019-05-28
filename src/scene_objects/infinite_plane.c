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

t_figure	infinite_plane_init(void)
{
	t_figure	figure;

	figure.type = InfinitePlane;
	figure.vector1 = (cl_float3){{0.0f, 1.0f, 0.0f}};
	figure.vector2 = (cl_float3){{0.0f, 0.0f, 0.0f}};
	figure.color = 0xffffff;
	figure.spectacular = 0;
	figure.reflection = 0;
	return (figure);
}
