/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figure_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/03 14:47:44 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_transparency(t_figure *figure, JSON_Object *obj)
{
	if (json_object_has_value_of_type(obj, "transparency", JSONNumber))
		figure->transparency = (cl_float)json_object_get_number(obj,
				"transparency");
	else
		ft_putendl_fd("Unknown or invalid transparency. Default applied",
				STDERR_FILENO);
	if (figure->transparency < 0.0f)
	{
		ft_putendl_fd("Transparency less than 0. 0 applied",
				STDERR_FILENO);
		figure->transparency = 0;
	}
	if (figure->transparency > 1.0f)
	{
		ft_putendl_fd("Transparency greater than 1. 1 applied",
				STDERR_FILENO);
		figure->transparency = 1;
	}
}

static void	get_density(t_figure *figure, JSON_Object *obj)
{
	if (json_object_has_value_of_type(obj, "density", JSONNumber))
		figure->density = (cl_float)json_object_get_number(obj,
				"density");
	else
		ft_putendl_fd("Unknown or invalid density. Default applied",
				STDERR_FILENO);
}

static void	get_reflection(t_figure *figure, JSON_Object *obj)
{
	if (json_object_has_value_of_type(obj, "reflection", JSONNumber))
		figure->reflection = (cl_float)json_object_get_number(obj,
				"reflection");
	else
		ft_putendl_fd("Unknown or invalid reflection. Default applied",
				STDERR_FILENO);
	if (figure->reflection < 0.0f)
	{
		ft_putendl_fd("Reflection less than 0. 0 applied",
				STDERR_FILENO);
		figure->reflection = 0;
	}
	if (figure->reflection > 1.0f)
	{
		ft_putendl_fd("Reflection greater than 1. 1 applied",
				STDERR_FILENO);
		figure->reflection = 1;
	}
}

void		get_figure_params(t_figure *figure, JSON_Object *obj)
{
	if (json_object_has_value_of_type(obj, "color", JSONString) &&
		check_hex(json_object_get_string(obj, "color")))
		figure->color = ft_hexatoi(json_object_get_string(obj, "color"));
	else
		ft_putendl_fd("Unknown or invalid color. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "spectacular", JSONNumber))
		figure->spectacular = (cl_float)json_object_get_number(obj,
				"spectacular");
	else
		ft_putendl_fd("Unknown or invalid spectacular. Default applied",
				STDERR_FILENO);
	get_reflection(figure, obj);
	get_density(figure, obj);
	get_transparency(figure, obj);
	get_figure_texture(figure, obj);
}
