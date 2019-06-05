/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/05 14:22:02 by tmaluh           ###   ########.fr       */
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
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# ifdef DOT
#  undef DOT
# endif

struct			s_dot
{
	int32_t	x;
	int32_t	y;
};

# define DOT typedef struct	s_dot Dot

DOT;

enum			e_figure
{
	BadFigure = 0,
	Sphere = 1,
	InfinitePlane = 2,
	InfiniteCylinder = 3,
	InfiniteCone = 4,
	Cylinder = 5,
	Cone = 6,
	Triangle = 7,
	Ellipsoid = 8
};

enum			e_light
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
}				t_light;

typedef struct	s_figure
{
	cl_float		spectacular;
	cl_float		reflection;
	cl_float		transparency;
	cl_float		density;
	cl_int			color;
	enum e_figure	type;
	cl_float3		vector1;
	cl_float3		vector2;
	cl_float3		vector3;
	cl_float		param1;
	cl_float		param2;
	cl_float		param3;
	char			*texture;
	Dot				spos;
	Dot				epos;
}				t_figure;

typedef struct	s_ray
{
	cl_float3		o;
	cl_float3		v;
}				t_ray;

typedef struct	s_cl
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

}				t_cl;

typedef struct	s_view
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	cl_int			*scene;
	t_figure		*figures;
	size_t			figures_count;
	t_light			*lights;
	size_t			lights_count;
	cl_int			*params;
	cl_int			width;
	cl_int			height;
	cl_int			antialiasing;
	cl_int			depth;
	t_ray			*cam;
	t_cl			*cl;
	Uint32			*tex_pxls;
}				t_view;

int				check_hex(const char *str);
int				ft_hexatoi(const char *str);
cl_float3		get_vector(JSON_Array *arr, cl_float3 def);
void			get_figure_params(t_figure *figure, JSON_Object *obj);
void			get_figure_texture(t_figure *figure, JSON_Object *obj);
void			get_space(t_view *view, char *filename);
void			get_sphere(t_figure *figure, JSON_Object *obj);
void			get_infinite_plane(t_figure *figure, JSON_Object *obj);
void			get_infinite_cone(t_figure *figure, JSON_Object *obj);
void			get_infinite_cylinder(t_figure *figure, JSON_Object *obj);
void			get_cone(t_figure *figure, JSON_Object *obj);
void			get_cylinder(t_figure *figure, JSON_Object *obj);
void			get_triangle(t_figure *figure, JSON_Object *obj);
void			get_ellipsoid(t_figure *figure, JSON_Object *obj);
void			get_lights(t_view *view, JSON_Object *root);
void			get_cam(t_view *view, JSON_Object *root);
void			get_params(t_view *view, JSON_Object *root);
t_figure		sphere_init();
t_figure		cylinder_init();
t_figure		infinite_plane_init();
t_figure		infinite_cylinder_init();
t_figure		infinite_cone_init();
t_figure		cone_init();
t_figure		triangle_init();
t_figure		ellipsoid_init();
t_light			light_init(enum e_light type, cl_float3 position,
		cl_float intens);
cl_float3		normalize(cl_float3 unnormalized);
cl_float		length(cl_float3 vector);
cl_float		dot(cl_float3 vector1, cl_float3 vector2);
cl_float3		sub(cl_float3 a, cl_float3 b);
void			cl_init(t_view *view);
void			cl_run_kernel(t_view *view);
void			params_init(t_view *view);

/*
**	Ya _ipal etot C: structs
*/

enum	e_bool {false, true} __attribute__((packed));

# ifdef FREE
#  undef FREE
# endif

# define FREE(trash, fn_del) if ((trash)) {fn_del((trash)); (trash) = NULL;}

# ifdef BOOL
#  undef BOOL
# endif

# define BOOL typedef enum e_bool bool

BOOL;

typedef struct	s_helper
{
	SDL_Surface			**tex_surf;
	size_t				summ_height;
	size_t				max_width;
	size_t				textured_objs;
	Dot					*spos;
	Dot					*epos;
}				t_helper;

/*
**	Ya _ipal etot C: funcs
*/
SDL_Surface		*sdl_load_image(const char *const path,
								const SDL_PixelFormat *format,
								SDL_Surface *dst);
Uint32			*rt_sdl_load_textures(t_figure *restrict const objs,
								const size_t max_objs,
								const SDL_PixelFormat *format);

/*
**	Ya raz_ipal etot C.
*/

#endif
