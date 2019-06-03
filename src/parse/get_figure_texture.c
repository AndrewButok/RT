/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figure_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/03 14:49:30 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_figure_texture(t_figure *figure, JSON_Object *obj)
{
	figure->texture = NULL;
	if (json_object_has_value_of_type(obj, "texture", JSONString))
		figure->texture = (char*)json_object_get_string(obj, "texture");
}
