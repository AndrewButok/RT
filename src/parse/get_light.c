/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 18:43:39 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	get_parallel_light(t_light *light, JSON_Object *obj)
{
	*light = light_init(Parallel, (cl_float3){{0, 0, 0}}, 0);
	if (!(json_object_has_value_of_type(obj, "intensity", JSONNumber) &&
		json_object_has_value_of_type(obj, "vector", JSONArray)))
		return (false);
	light->intensity = (cl_float)json_object_get_number(obj, "intensity");
	if (light->intensity < 0 || light->intensity > 1)
		return (false);
	if (!get_vector(json_object_get_array(obj, "vector"), &(light->position)))
		return (false);
	light->position = normalize(light->position);
	return (true);
}

bool	get_ambient_light(t_light *light, JSON_Object *obj)
{
	*light = light_init(Ambient, (cl_float3){{0, 0, 0}}, 0);
	if (!(json_object_has_value_of_type(obj, "intensity", JSONNumber)))
		return (false);
	light->intensity = (cl_float)json_object_get_number(obj, "intensity");
	if (light->intensity < 0 || light->intensity > 1)
		return (false);
	return (true);
}

bool	get_point_light(t_light *light, JSON_Object *obj)
{
	*light = light_init(Point, (cl_float3){{0, 0, 0}}, 0);
	if (!(json_object_has_value_of_type(obj, "intensity", JSONNumber) &&
		json_object_has_value_of_type(obj, "position", JSONArray)))
		return (false);
	light->intensity = (cl_float)json_object_get_number(obj, "intensity");
	if (light->intensity < 0 || light->intensity > 1)
		return (false);
	if (!get_vector(json_object_get_array(obj, "position"), &(light->position)))
		return (false);
	return (true);
}

bool	get_light(t_light *light, JSON_Value *val)
{
	const char		*type;
	JSON_Object		*obj;

	if (val == NULL || json_value_get_type(val) != JSONObject)
		return (false);
	obj = json_value_get_object(val);
	if (obj == NULL || !json_object_has_value_of_type(obj, "type", JSONString))
		return (false);
	type = json_object_get_string(obj, "type");
	if (ft_strequ(type, "ambient"))
		return (get_ambient_light(light, obj));
	if (ft_strequ(type, "point"))
		return (get_point_light(light, obj));
	if (ft_strequ(type, "parallel"))
		return (get_parallel_light(light, obj));
	return (false);
}

bool	get_lights(t_view *view, JSON_Object *obj)
{
	bool		err;
	JSON_Array	*arr;
	int			i;
	int			total;

	err = true;
	if (!json_object_has_value_of_type(obj, "lights", JSONArray))
		return (false);
	arr = json_object_get_array(obj, "lights");
	if (arr == NULL || (total = json_array_get_count(arr)) <= 0)
		return (false);
	if ((view->lights = (t_light*)malloc(sizeof(t_light) * total)) == NULL)
		return (false);
	view->lights_count = total;
	i = -1;
	while (++i < total && err)
		err = get_light(&(view->lights[i]),
			json_array_get_value(arr, i));
	return (err);
}
