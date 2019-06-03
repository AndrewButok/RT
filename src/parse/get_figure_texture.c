/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figure_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_figure_texture(t_figure *figure, JSON_Object *obj)
{
	figure->texture = NULL;
	if (json_object_has_value_of_type(obj, "texture", JSONString))
		figure->texture = json_object_get_string(obj, "texture");
}
