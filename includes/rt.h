/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define CL_SILENCE_DEPRECATION
# include "libft.h"
# include "get_next_line.h"
# include "parson.h"
# include <errno.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <OpenCL/cl.h>
# include <SDL.h>

enum					e_figure
{
	BadFigure = 0,
	Sphere = 1,
	InfinitePlane = 2,
	InfiniteCylinder = 3,
	InfiniteCone = 4,
	Cylinder = 5
};

enum					e_light
{
	BadLight = -1,
	Ambient = 0,
	Point = 1
};

typedef struct	s_light
{
	enum e_light	type;
	cl_float3		position;
	cl_float		intensity;
}						t_light;

typedef struct	s_figure
{
	cl_float		reflection;
	cl_int			color;
	enum e_figure 	type;
	cl_float3		vector1;
	cl_float3		vector2;
	cl_float		param1;
	cl_float		param2;
}						t_figure;

typedef struct	s_ray
{
	cl_float3		o;
	cl_float3		v;
}						t_ray;

typedef struct			s_cl
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				buf_figures;
	cl_mem				buf_lights;
	cl_mem				buf_cam;
	cl_mem				buf_img;
	cl_mem				buf_param;
	size_t				works;

}						t_cl;

typedef struct			s_view
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	cl_int			*scene;
	t_figure		*figures;
	size_t 			figures_count;
	t_light			*lights;
	size_t 			lights_count;
	cl_int			*params;
	cl_int 			width;
	cl_int 			height;
	cl_int 			rays_count;
	t_ray			*cam;
	t_cl			*cl;
}						t_view;

int						check_hex(const char *str);
int						ft_hexatoi(const char *str);
cl_float3				get_vector(JSON_Array *arr, cl_float3 def);
void					get_color_reflection(t_figure *figure, JSON_Object *obj);
void					get_space(t_view *view, char *filename);
void					get_sphere(t_figure *figure, JSON_Object *obj);
void					get_infinite_plane(t_figure *figure, JSON_Object *obj);
void					get_infinite_cone(t_figure *figure, JSON_Object *obj);
void					get_infinite_cylinder(t_figure *figure,
		JSON_Object *obj);
void					get_cylinder(t_figure *figure, JSON_Object *obj);
void					get_lights(t_view *view, JSON_Object *root);
void					get_cam(t_view *view, JSON_Object *root);
void					get_params(t_view *view, JSON_Object *root);
t_figure				sphere_init();
t_figure				cylinder_init();
t_figure				infinite_plane_init();
t_figure				infinite_cylinder_init();
t_figure				infinite_cone_init();
t_light					light_init(enum e_light type, cl_float3 position,
		cl_float intens);
cl_float3				vector_normalize(cl_float3 unnormalized);
cl_float				vector_length(cl_float3 vector);
cl_float				vector_scalar_multiple(cl_float3 vector1,
		cl_float3 vector2);
void					cl_init(t_view *view);
void					cl_run_kernel(t_view *view);
void					params_init(t_view *view);

#endif
