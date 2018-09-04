/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*get_kernel(void)
{
	char	*rslt;
	char	*a;
	char	*b;
	int		fd;
	int		e;

	errno = 0;
	fd = open("./src/do_rt.cl", O_RDONLY);
	rslt = NULL;
	b = NULL;
	while ((e = get_next_line(fd, &b)) > 0)
	{
		a = rslt;
		rslt = ft_strjoin(a, b);
		ft_strdel(&a);
		ft_strdel(&b);
	}
	ft_strdel(&b);
	if (e == -1)
	{
		perror("Kernel file error");
		exit(0);
	}
	close(fd);
	return (rslt);
}

static void	cl_buf_init(t_view *view)
{
	int		err;

	view->cl->buf_img = clCreateBuffer(view->cl->context,
			CL_MEM_COPY_HOST_PTR,
			sizeof(cl_int) * view->width * view->height, view->scene, &err);
	view->cl->buf_figures = clCreateBuffer(view->cl->context,
			CL_MEM_COPY_HOST_PTR,
			sizeof(t_figure) * view->figures_count, view->figures, &err);
	view->cl->buf_lights = clCreateBuffer(view->cl->context,
			CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * view->lights_count, view->lights, &err);
	view->cl->buf_cam = clCreateBuffer(view->cl->context,
			CL_MEM_COPY_HOST_PTR,
			sizeof(t_ray), view->cam, &err);
	params_init(view);
	view->cl->buf_param	= clCreateBuffer(view->cl->context,
			CL_MEM_COPY_HOST_PTR, sizeof(cl_int) * 6, view->params, &err);
}

static void	cl_kernel_buf_assign(t_view *view)
{
	clSetKernelArg(view->cl->kernel, 0, sizeof(cl_mem), &view->cl->buf_figures);
	clSetKernelArg(view->cl->kernel, 1, sizeof(cl_mem), &view->cl->buf_lights);
	clSetKernelArg(view->cl->kernel, 2, sizeof(cl_mem), &view->cl->buf_cam);
	clSetKernelArg(view->cl->kernel, 3, sizeof(cl_mem), &view->cl->buf_img);
	clSetKernelArg(view->cl->kernel, 4, sizeof(cl_mem), &view->cl->buf_param);

}

static void	cl_kernel_init(t_view *view)
{
	char	*src;
	int		err;

	src = get_kernel();
	view->cl->program = clCreateProgramWithSource(view->cl->context, 1,
			(const char**)&src, NULL, &err);
	free(src);
	clBuildProgram(view->cl->program, 1, &view->cl->device, NULL, NULL, &err);
	view->cl->kernel = clCreateKernel(view->cl->program, "do_rt", &err);
	if (err != 0)
	{
		ft_putendl_fd("Ok, you have change it. It not works. What's next?", 2);
		exit(0);
	}
	cl_buf_init(view);
	cl_kernel_buf_assign(view);
	view->cl->works = (size_t)view->width * view->height;
}

void	cl_init(t_view *view)
{
	view->cl = (t_cl*)malloc(sizeof(t_cl));
	clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &(view->cl->device), NULL);
	view->cl->context = clCreateContext(NULL, 1, &(view->cl->device),
	 		NULL, NULL, NULL);
	view->cl->queue = clCreateCommandQueue(view->cl->context, view->cl->device,
	 		0, NULL);
	cl_kernel_init(view);
	cl_run_kernel(view);
}
