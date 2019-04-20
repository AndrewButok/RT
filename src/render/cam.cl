/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.cl                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:44:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	cam_rotate(t_ray *ray, float3 rotate_v)
{
	float n1, n2;

	rotate_v *= (M_PI_F / 180.0f);
	if (rotate_v.x != 0)
	{
		n1 = ray->v.y * cos(rotate_v.x) + ray->v.z * sin(rotate_v.x);
		n2 = ray->v.z * cos(rotate_v.x) - ray->v.y * sin(rotate_v.x);
		ray->v.y = n1;
		ray->v.z = n2;
	}
	if (rotate_v.y != 0)
	{
		n1 = ray->v.x * cos(rotate_v.y) + ray->v.z * sin(rotate_v.y);
		n2 = ray->v.z * cos(rotate_v.y) - ray->v.x * sin(rotate_v.y);
		ray->v.x = n1;
		ray->v.z = n2;
	}
	if (rotate_v.z != 0)
	{
		n1 = ray->v.x * cos(rotate_v.z) + ray->v.y * sin(rotate_v.z);
		n2 = ray->v.y * cos(rotate_v.z) - ray->v.x * sin(rotate_v.z);
		ray->v.x = n1;
		ray->v.y = n2;
	}
}