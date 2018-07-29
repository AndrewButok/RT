/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_figure(t_view *view, JSON_Object *figure, size_t i)
{
	const char		*type;

	if (view->figures == NULL && i == 0)
	{
		view->figures = (t_figure*)malloc(sizeof(t_figure));
		view->figures_count = 1;
	}
	if ((type = json_object_get_string(figure, "type")) != NULL)
	{
		if (ft_strequ(type, "sphere"))
			get_sphere(&(view->figures[i]), figure);
		else if (ft_strequ(type, "plane"))
			get_infinite_plane(&(view->figures[i]), figure);
		else if (ft_strequ(type, "cone"))
			get_infinite_cone(&(view->figures[i]),figure);
		else if (ft_strequ(type, "cylinder"))
			get_infinite_cylinder(&(view->figures[i]),figure);
		else
		{
			ft_putendl_fd("Unknown figure found.Skipped.", STDERR_FILENO);
			view->figures[i].type = BadFigure;
		}
	}
	else
		ft_putendl_fd("Unknown figure type.Skipped.",STDERR_FILENO);

}

void	choose_figure_parse(t_view *view, JSON_Value *root)
{
	JSON_Array	*arr;
	JSON_Object	*fig;
	size_t		i;

	if (json_value_get_type(root) == JSONArray)
	{
		arr = json_value_get_array(root);
		view->figures_count = json_array_get_count(arr);
		view->figures = (t_figure*)malloc(sizeof(t_figure) *
										  view->figures_count);
		i = view->figures_count;
		while (i > 0)
		{
			if ((fig = json_array_get_object(arr, --i)) != NULL)
				get_figure(view, fig, i);
		}
		return ;
	}
	if (json_value_get_type(root) == JSONObject)
	{
		get_figure(view, json_value_get_object(root), 0);
		return ;
	}
	ft_putendl_fd("Wrong figure obj type. It must be obj or array.",
				  STDERR_FILENO);
}


void	get_figures(t_view *view, JSON_Object *root)
{
	JSON_Value	*val;

	val = json_object_get_value(root, "figures");
	if (val == NULL)
	{
		ft_putendl_fd("Figures not found in your file.", STDERR_FILENO);
		return ;
	}
	choose_figure_parse(view, val);
}

void	get_space(t_view *view, char *filename)
{
	JSON_Value 	*root;
	JSON_Object	*robj;

	root = json_parse_file(filename);
	if (root == NULL)
	{
		ft_putendl_fd("Parse error. Chech your file", STDERR_FILENO);
		exit(0);
	}
	robj = json_value_get_object(root);
	get_figures(view, robj);
	get_lights(view, robj);

}