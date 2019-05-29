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

static void	get_rays(t_view *view, JSON_Object *params)
{
	if (json_object_has_value_of_type(params, "antialias", JSONNumber))
		view->rays_count = (int)json_object_get_number(params, "antialias");
	else
	{
		ft_putendl("Antialias parameter is absent. Default applied");
		view->rays_count = 1;
		return ;
	}
	if (view->rays_count > 100 || view->rays_count < 1)
	{
		ft_putendl("Invalid antialias parameter. Default applied");
		view->rays_count = 1;
	}
}

static void	get_depth(t_view *view, JSON_Object *params)
{
	if (json_object_has_value_of_type(params, "depth", JSONNumber))
		view->depth = (int)json_object_get_number(params, "depth");
	else
	{
		ft_putendl("Depth parameter is absent. Default applied");
		view->depth = 0;
		return ;
	}
	if (view->depth > 5 || view->depth < 0)
	{
		ft_putendl("Invalid depth parameter. Default applied");
		view->depth = 0;
	}
}

void		get_params(t_view *view, JSON_Object *root)
{
	JSON_Object	*val;

	view->width = 800;
	view->height = 600;
	view->rays_count = 1;
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
		get_depth(view, val);
	}
	else
		ft_putendl_fd("Default screen params applied.", STDERR_FILENO);
}
