/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/07 20:19:37 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_ambient_light(t_light *light, JSON_Object *obj)
{
	*light = light_init(Ambient, (cl_float3){{0, 0, 0}}, 0);
	if (json_object_has_value_of_type(obj, "intensity", JSONNumber))
		light->intensity = (cl_float)json_object_get_number(obj, "intensity");
	else
		ft_putendl_fd("Intensity parameter not found. Default applied.",
				STDERR_FILENO);
	ft_putendl("\x1b[32mAmbient light parsed.");
}

void	get_point_light(t_light *light, JSON_Object *obj)
{
	*light = light_init(Point, (cl_float3){{0, 0, 0}}, 0);
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
	ft_putendl("\x1b[32mPoint light parsed.");
}

void	get_light(t_view *view, JSON_Object *obj, size_t i)
{
	const char		*type;

	if (view->lights == NULL && i == 0)
	{
		view->lights = (t_light*)malloc(sizeof(t_light));
		view->lights_count = 1;
	}
	if ((type = json_object_get_string(obj, "type")) != NULL)
	{
		if (ft_strequ(type, "ambient"))
			get_ambient_light(&(view->lights[i]), obj);
		else if (ft_strequ(type, "point"))
			get_point_light(&(view->lights[i]), obj);
		else if (ft_strequ(type, "direct"))
			get_direct_light(&(view->lights[i]), obj);
		else
		{
			ft_putendl_fd("Unknown light found. Skipped.", STDERR_FILENO);
			view->lights[i].type = BadLight;
		}
	}
	else
		ft_putendl_fd("Unknown light type.Skipped.", STDERR_FILENO);
}

void	choose_light_parse(t_view *view, JSON_Value *value)
{
	JSON_Array	*arr;
	JSON_Object	*fig;
	size_t		i;

	if (json_value_get_type(value) == JSONArray)
	{
		arr = json_value_get_array(value);
		view->lights_count = json_array_get_count(arr);
		view->lights = (t_light*)malloc(sizeof(t_light) *
				view->lights_count);
		i = view->lights_count;
		while (i > 0)
		{
			if ((fig = json_array_get_object(arr, --i)) != NULL)
				get_light(view, fig, i);
		}
		return ;
	}
	if (json_value_get_type(value) == JSONObject)
	{
		get_light(view, json_value_get_object(value), 0);
		return ;
	}
	ft_putendl_fd("Wrong light obj type. It must be obj or array.",
			STDERR_FILENO);
}

void	get_lights(t_view *view, JSON_Object *root)
{
	JSON_Value	*val;

	val = json_object_get_value(root, "lights");
	if (val == NULL)
	{
		ft_putendl_fd("Lights is not found.", STDERR_FILENO);
		return ;
	}
	choose_light_parse(view, val);
}
