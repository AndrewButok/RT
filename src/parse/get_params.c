/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	get_rays(t_view *view, JSON_Object *params)
{
	view->rays_count = 1;
	if (json_object_has_value_of_type(params, "antialias", JSONNumber))
		view->rays_count = (int)json_object_get_number(params, "antialias");
	else
		ft_putendl("Antialias parameter is absent. Default applied");
	if (view->rays_count > 90 || view->rays_count < 1)
	{
		ft_putendl("Invalid antialias parameter. Default applied");
		view->rays_count = 1;
	}
}

void	get_params(t_view *view, JSON_Object *root)
{
	JSON_Object	*val;

	view->width = 800;
	view->height = 600;
	val = json_object_get_object(root, "params");
	if (val != NULL)
	{
		if (json_object_has_value_of_type(val, "width", JSONNumber))
			view->width = (cl_int)json_object_get_number(val, "width");
		else
			ft_putendl_fd("Height parameter isn't present or illegal."
				 "Default applied", STDERR_FILENO);
		if (json_object_has_value_of_type(val, "height", JSONNumber))
			view->height = (cl_int)json_object_get_number(val, "height");
		else
			ft_putendl_fd("Height parameter isn't present or illegal."
			  "Default applied", STDERR_FILENO);
		get_rays(view, val);
	}
	else
	{
		ft_putendl_fd("Default screen params applied.", STDERR_FILENO);
		view->width = 800;
		view->height = 600;
		view->rays_count = 1;
	}
}
