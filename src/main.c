/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 01:11:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/14 15:50:41 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#define ESC_KEY 53

static void	view_init(t_view **view_ptr, char *filename)
{
	t_view		*view;

	errno = 0;
	view = (t_view*)malloc(sizeof(t_view));
	if (errno != 0)
	{
		perror("View malloc error");
	}
	*view_ptr = view;
	space_init(filename, view);
	view->mlx = mlx_init();
	view->win = mlx_new_window(view->mlx, WIN_WIDTH, WIN_HEIGHT, "RTv1");
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	view->scene = (int*)mlx_get_data_addr(view->img, &view->bits_per_pixel,
			&view->size_line, &view->endian);
	do_rt(view);
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	mlx_destroy_image(view->mlx, view->img);
}

int			do_keyboard(int key, t_view *view)
{
	if (key == ESC_KEY)
		exit_x(view);
	return (1);
}

int			exit_x(t_view *view)
{
	exit(1);
	view = NULL;
	return (0);
}

int			main(int argc, char **argv)
{
	t_view *view;

	if (argc != 2)
	{
		ft_putstr("usage: RTv1 scene_filename\n");
		return (0);
	}
	view_init(&view, argv[1]);
	mlx_hook(view->win, 2, 0, &do_keyboard, view);
	mlx_hook(view->win, 17, 1L << 17, &exit_x, view);
	mlx_loop(view->mlx);
	return (0);
}
