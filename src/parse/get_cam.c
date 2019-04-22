/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_cam(t_view *view, JSON_Object *root)
{
	JSON_Object *cam;

	cam = json_object_get_object(root, "cam");
	if (cam == NULL)
		return ;
	view->cam = (t_ray*)malloc(sizeof(t_ray));
	if (json_object_has_value_of_type(cam, "position", JSONArray))
		view->cam->o = get_vector(json_object_get_array(cam,
				"position"), view->cam->o);
	else
		ft_putendl_fd("Unknown cam position. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(cam, "rotation", JSONArray))
		view->cam->v = get_vector(json_object_get_array(cam,
				"rotation"), view->cam->v);
	else
		ft_putendl_fd("Unknown cam rotation. Default applied", STDERR_FILENO);
}
