/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 21:31:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 21:31:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_array_type(JSON_Array *array, JSON_Value_Type type)
{
	size_t	i;

	i = json_array_get_count(array);
	while (i > 0 && json_value_get_type(json_array_get_value(array, i - 1)) ==
			type)
		i--;
	if (i == 0)
		return (1);
	return (0);
}

void	parse_triangle(JSON_Object *triangle, t_view *view)
{
	JSON_Array	*points;
	t_figure	*figure;
	t_vector	v[3];
	size_t		i;

	if ((points = json_object_get_array(triangle, "points")) == NULL &&
			json_array_get_count(points) != 3 &&
			check_array_type(points, JSONArray) &&
			check_array_type(json_array_get_array(points, 0), JSONNumber) &&
			check_array_type(json_array_get_array(points, 1), JSONNumber) &&
			check_array_type(json_array_get_array(points, 2), JSONNumber))
		ft_putendl_fd("Triangle have no points array or this array is broken. "
				"Figure skipped",
				STDERR_FILENO);
	i = 3;
	while (i > 0)
	{
		i--;
	}

	
	
}
