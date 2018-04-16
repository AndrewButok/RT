/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 11:47:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/13 11:47:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			parse_scene(char *filename, t_view *view)
{
	JSON_Value		*root;
	JSON_Value_Type	type;
	JSON_Object		*root_obj;

	root = json_parse_file(filename);
	type = json_value_get_type(root);
	if (type != JSONObject)

	json_value_free(root);
}
