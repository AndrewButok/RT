/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/08 15:15:30 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	params_init(t_view *view)
{
	view->params = (cl_int*)malloc(sizeof(cl_int) * 7);
	view->params[0] = view->width;
	view->params[1] = view->height;
	view->params[2] = (int)view->figures_count;
	view->params[3] = (int)view->lights_count;
	view->params[4] = view->antialiasing;
	view->params[5] = view->depth;
	view->params[6] = view->filter;
}

void	cl_run_kernel(t_view *view)
{
	clEnqueueNDRangeKernel(view->cl->queue, view->cl->kernel, 1, NULL,
			&view->cl->works, NULL, 0, NULL, NULL);
	clFlush(view->cl->queue);
	clEnqueueReadBuffer(view->cl->queue, view->cl->buf_img, CL_TRUE, 0,
						sizeof(cl_int) * view->width * view->height,
						view->scene, 0, NULL, NULL);
	clFinish(view->cl->queue);
}
