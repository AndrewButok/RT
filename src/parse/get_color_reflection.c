/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_reflection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_color_reflection(t_figure *figure, JSON_Object *obj)
{
	if (json_object_has_value_of_type(obj, "color", JSONString) &&
		check_hex(json_object_get_string(obj, "color")))
		figure->color = ft_hexatoi(json_object_get_string(obj, "color"));
	else
		ft_putendl_fd("Unknown or invalid color. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(obj, "reflection", JSONNumber))
		figure->reflection = (cl_float)json_object_get_number(obj,
				"reflection");
	else
		ft_putendl_fd("Unknown or invalid reflection. Default applied",
				STDERR_FILENO);
}
