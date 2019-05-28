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

t_figure	infinite_cone_init(void)
{
	t_figure figure;

	figure.vector1 = (cl_float3){{0, 0, 0}};
	figure.vector2 = (cl_float3){{0, -1, 0}};
	figure.param1 = 1;
	figure.color = 0xffffff;
	figure.spectacular = 0;
	figure.type = InfiniteCone;
	return (figure);
}
