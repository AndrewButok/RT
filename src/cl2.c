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

void	cl_run_kernel(t_view *view)
{
	clEnqueueNDRangeKernel(view->cl->queue, view->cl->kernel, 1, NULL,
			&view->cl->works, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(view->cl->queue, view->cl->buf_img, CL_TRUE, 0,
						sizeof(cl_int) * WIN_HEIGHT * WIN_WIDTH,
						view->scene, 0, NULL, NULL);
	clFinish(view->cl->queue);
}

