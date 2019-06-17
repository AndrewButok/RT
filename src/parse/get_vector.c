/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 11:53:38 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	get_vector(JSON_Array *arr, cl_float3 *vector)
{
	size_t i;
	size_t c;

	c = json_array_get_count(arr);
	if (c != 3)
		return (false);
	i = 0;
	while (i < c)
	{
		if (json_value_get_type(json_array_get_value(arr, i)) != JSONNumber)
			return (false);
		i++;
	}
	*vector = ((cl_float3){{(cl_float)json_array_get_number(arr, 0),
						(cl_float)json_array_get_number(arr, 1),
						(cl_float)json_array_get_number(arr, 2)}});
	return (true);
}
