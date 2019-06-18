/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/18 15:14:55 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	get_cam(t_view *view, JSON_Object *root)
{
	JSON_Object *cam;

	if (root == NULL || !json_object_has_value_of_type(root, "cam", JSONObject))
		return (false);
	cam = json_object_get_object(root, "cam");
	if (cam == NULL ||
		!(json_object_has_value_of_type(cam, "position", JSONArray) &&
		json_object_has_value_of_type(cam, "rotation", JSONArray)))
		return (false);
	view->cam = (t_ray*)malloc(sizeof(t_ray));
	if (!get_vector(json_object_get_array(cam, "position"), &(view->cam->o)))
		return (false);
	if (!get_vector(json_object_get_array(cam, "rotation"), &(view->cam->v)))
		return (false);
	return (true);
}
