/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:19:00 by abutok            #+#    #+#             */
/*   Updated: 2018/02/21 12:19:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float	vector_scalar_multiple(cl_float3 vector1, cl_float3 vector2)
{
	return (vector1.x * vector2.x +
			vector1.y * vector2.y +
			vector1.z * vector2.z);
}

cl_float	vector_length(cl_float3 vector)
{
	return (sqrtf(vector_scalar_multiple(vector, vector)));
}

cl_float3	vector_normalize(cl_float3 unnormalized)
{
	cl_float len;

	len = vector_length(unnormalized);
	return ((cl_float3){{unnormalized.x / len,
						unnormalized.y / len,
						unnormalized.z / len}});
}
