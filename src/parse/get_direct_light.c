/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direct_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 20:16:08 by abutok            #+#    #+#             */
/*   Updated: 2019/06/08 13:40:13 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_parallel_light(t_light *light, JSON_Object *obj)
{
	*light = light_init(Parallel, (cl_float3){{0, 0, 0}}, 0);
	if (json_object_has_value_of_type(obj, "intensity", JSONNumber))
		light->intensity = (cl_float)json_object_get_number(obj, "intensity");
	else
		ft_putendl_fd("Intensity parameter not found. Default applied.",
				STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "position", JSONArray))
		light->position = get_vector(json_object_get_array(obj, "position"),
				light->position);
	else
		ft_putendl_fd("Position not found. Default applied.",
				STDERR_FILENO);
	ft_putendl("\x1b[32mParallel light parsed.");
}
