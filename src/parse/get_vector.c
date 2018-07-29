/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	get_vector(JSON_Array *arr, cl_float3 def)
{
	size_t i;
	size_t c;

	c = json_array_get_count(arr);
	if (c != 3)
	{
		ft_putendl_fd("Wrong vector size. Default applied", STDERR_FILENO);
		return (def);
	}
	i = 0;
	while (i < c)
	{
		if (json_value_get_type(json_array_get_value(arr, i)) != JSONNumber)
		{
			ft_putendl_fd("Wrong vector format. Default applied",
						  STDERR_FILENO);
			return (def);
		}
		i++;
	}
	return ((cl_float3){{(cl_float)json_array_get_number(arr, 0),
						(cl_float)json_array_get_number(arr, 1),
						(cl_float)json_array_get_number(arr, 2)}});
}
