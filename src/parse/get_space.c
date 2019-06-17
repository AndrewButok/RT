/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/16 21:59:28 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef	bool(*t_parse_function)(t_figure*, JSON_Object*, SDL_PixelFormat*);

t_parse_function	get_parse_function(const char *type)
{
	if (ft_strequ(type, "sphere"))
		return (&get_sphere);
	// else if (ft_strequ(type, "plane"))
	// 	return (&get_infinite_plane);
	// else if (ft_strequ(type, "infinite_cone"))
	// 	return (&get_infinite_cone);
	// else if (ft_strequ(type, "infinite_cylinder"))
	// 	return (&get_infinite_cylinder);
	// else if (ft_strequ(type, "cylinder"))
	// 	return (&get_cylinder);
	// else if (ft_strequ(type, "cone"))
	// 	return (&get_cone);
	// else if (ft_strequ(type, "triangle"))
	// 	return (&get_triangle);
	// else if (ft_strequ(type, "ellipsoid"))
	// 	return (&get_ellipsoid);
	else
		return (NULL);
}

static bool			get_figure(t_figure *figure, JSON_Value *val, SDL_PixelFormat *px)
{
	JSON_Object			*obj;
	t_parse_function	parse_figure;

	if (val == NULL || json_value_get_type(val) != JSONObject)
		return (false);
	obj = json_value_get_object(val);
	if (obj == NULL || !json_object_has_value_of_type(obj, "type", JSONString))
		return (false);
	parse_figure = get_parse_function(json_object_get_string(obj, "type"));
	return (parse_figure(figure, obj, px));
}

static bool			get_figures(t_view *view, JSON_Object *obj)
{
	bool		err;
	JSON_Array	*arr;
	int			i;
	int			total;
	
	err = true;
	if (!json_object_has_value_of_type(obj, "figures", JSONArray))
		return (false);
	arr = json_object_get_array(obj, "figures");
	if (arr == NULL || (total = json_array_get_count(arr)) <= 0)
		return (false);
	if ((view->figures = (t_figure*)malloc(sizeof(t_figure) * total)) == NULL)
		return (false);
	i = -1;
	while (++i < total && err)
		err = get_figure(&(view->figures[i]),
			json_array_get_value(arr, i), view->surface->format);
	return (err);
}

bool				get_space(t_view *view, char *filename)
{
	JSON_Value	*root;
	JSON_Object	*robj;

	if ((root = json_parse_file(filename)) == NULL)
		return (false);
	robj = json_value_get_object(root);
	if (!(get_params(view, robj) && get_figures(view, robj)))
	{
		json_value_free(root);
		return (false);
	}
	// get_params(view, robj);
	// get_lights(view, robj);
	// get_cam(view, robj);
	json_value_free(root);
	return (true);
}
