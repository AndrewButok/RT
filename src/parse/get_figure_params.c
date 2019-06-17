/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figure_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/17 14:48:14 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	get_rdt(t_figure *figure, JSON_Object *obj)
{
	if (!json_object_has_value_of_type(obj, "reflection", JSONNumber))
		return (false);
	figure->reflection = (cl_float)json_object_get_number(obj,
				"reflection");
	if (figure->reflection < 0.0f || figure->reflection > 1.0f)
		return (false);
	if (!json_object_has_value_of_type(obj, "transparency", JSONNumber))
		return (false);
	figure->transparency = (cl_float)json_object_get_number(obj,
				"transparency");
	if (figure->transparency < 0.0f || figure->transparency > 1.0f)
		return (false);
	if (!json_object_has_value_of_type(obj, "density", JSONNumber))
		return (false);
	figure->density = (cl_float)json_object_get_number(obj,
				"density");
	if (figure->density < 1.0f || figure->density > 2.0f)
		return (false);
	return (true);
}

bool		get_figure_params(t_figure *figure, JSON_Object *obj,
		SDL_PixelFormat *pf)
{
	if (!(json_object_has_value_of_type(obj, "color", JSONString) &&
		check_hex(json_object_get_string(obj, "color")) &&
		json_object_has_value_of_type(obj, "spectacular", JSONNumber)))
		return (false);
	figure->color = ft_hexatoi(json_object_get_string(obj, "color"));
	figure->spectacular = (cl_float)json_object_get_number(obj, "spectacular");
	if (figure->spectacular < 0 || figure->spectacular > 10000)
		return (false);
	if (!get_rdt(figure, obj))
		return (false);
	get_figure_texture(figure, obj, pf);
	return (true);
}
