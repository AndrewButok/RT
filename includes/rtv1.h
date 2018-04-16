/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/13 20:15:37 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "get_next_line.h"
# include "parson.h"
# include <errno.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define FOV_X 30
# define FOV_Y 30
# define LIGHT_TYPE_AMBIENT 0
# define LIGHT_TYPE_POINT 1
# define FIGURE_TYPE_PLANE 0
# define FIGURE_TYPE_SPHERE 1
# define FIGURE_TYPE_CYLINDER 2
# define FIGURE_TYPE_CONE 3

typedef union			u_color
{
	int				color;
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	}				spectrum;
}						t_color;

typedef struct			s_vector
{
	double			x;
	double			y;
	double			z;
}						t_vector;

typedef struct			s_light
{
	char			type;
	double			inten;
	t_vector		o;
	struct s_light	*next;
}						t_light;

/*
**	t_ray type represents origin of ray and his vector. Also for camera obj
**		this type setup coordinates of camera(o) and rotation angles(v).
**		In cylinder context this type represents start of cylinder axis(o)
**		and direction vector.
*/

typedef struct			s_ray
{
	t_vector		o;
	t_vector		v;
}						t_ray;

typedef struct			s_figure
{
	char			type;
	t_vector		center;
	double			radius;
	t_vector		axis;
	int				color;
	double			reflection;
	struct s_figure	*next;
}						t_figure;

typedef struct			s_space
{
	t_figure		*figures;
	t_light			*lights;
	t_ray			*cam;
}						t_space;

typedef	struct			s_lrt
{
	t_light			*light;
	t_vector		intersection;
	t_vector		normale;
	t_vector		vlight;
	t_ray			*buf;
	double			bright;
	double			reflected;
	double			nl_s;
}						t_lrt;

typedef struct			s_view
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*scene;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	t_space			*space;
}						t_view;

int						exit_x(t_view *view);
void					do_rt(t_view *view);
int						set_brightness(int color, double brightness,
		double bbrightness);
t_vector				vector_init(double x, double y, double z);
double					vscalar_multiple(t_vector a, t_vector b);
t_vector				vk_multiple(t_vector vector, double k);
t_vector				vsum(t_vector a, t_vector b);
t_vector				vsub(t_vector a, t_vector b);
t_vector				vnormalize(t_vector a);
double					vlen(t_vector a);
t_light					*light_init(char type, t_vector o, double intencity);
double					check_sphere_intersection(t_ray *ray, t_figure *figure);
double					get_sqr_solve(double a, double b, double d);
t_vector				get_normale(t_vector ray, t_figure *f);
t_vector				get_sphere_normale(t_vector p, t_figure *f);
t_figure				*sphere_init(t_vector center, double r, int color,
		double reflection);
double					check_plane_intersection(t_ray *ray, t_figure *figure);
t_vector				get_plane_normale(t_vector p, t_figure *f);
t_figure				*plane_init(t_vector normale, double d, int color,
		double reflection);
double					check_intersection(t_ray *ray, t_figure *figure);
int						check_intersections(t_ray *ray, t_figure *figures);
t_vector				get_intersection(t_ray *ray, double k);
t_ray					*ray_init(t_vector start, t_vector end);
void					space_init(char *filename, t_view *view);
void					cam_rotate(t_ray *ray, t_vector vector);
void					rotate_x(t_vector *ps, double l);
void					rotate_y(t_vector *ps, double l);
void					rotate_z(t_vector *ps, double l);
double					check_cylinder_intersection(t_ray *ray,
		t_figure *figure);
t_figure				*cylinder_init(t_ray *axis, double radius, int color,
		double reflection);
t_vector				get_cylinder_normale(t_vector p, t_figure *figure);
double					check_cone_intersection(t_ray *ray, t_figure *figure);
t_vector				get_cone_normale(t_vector p, t_figure *figure);
t_figure				*cone_init(t_ray *axis, double k, int color,
		double reflection);
void					opening_error(t_view *view);
void					parse_scene(char *filename, t_view *view);
void					del_strs(char ***strs);
double					ft_atod(char *str);
void					parse_cam(char **params, t_view *view);
int						check_paramnum(char **param, size_t n);
t_vector				parse_vector(char *str, t_vector vector);
void					vector_error(void);
void					parse_fplane(char **params, t_view *view);
void					add_light(t_light *light, t_view *view);
void					add_figure(t_figure *figure, t_view *view);
int						ft_hexatoi(char *str);
int						check_hex(char *str);
void					parse_fsphere(char **params, t_view *view);
void					parse_fcylinder(char **params, t_view *view);
void					parse_fcone(char **params, t_view *view);
void					parse_light(char **params, t_view *view);
double					get_double_param(char *str, char *name);

#endif
