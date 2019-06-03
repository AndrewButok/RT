/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sdl_load_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:58:23 by tmaluh            #+#    #+#             */
/*   Updated: 2019/06/03 15:24:55 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline bool	add_load_texture_surfaces(t_figure *restrict const objects,
										const size_t max_objs,
										const size_t texured_objs)
{
	SDL_Surface	*tex_surf[texured_objs];
	size_t		i;

	i = ~0L;
	if (*tex_surf)
	{
	}
	if (objects)
	{
	}
	while (max_objs > ++i)
		; // tex_surf[i] =
	return (true);
}

bool	rt_sdl_load_textures(t_figure *restrict const objs,
					const size_t max_objs)
{
	size_t		i;
	size_t		textured_objs;

	i = ~0L;
	textured_objs = ~0L;
	while (max_objs > ++i)
		if (objs[i].texture)
			++textured_objs;
	if (!add_load_texture_surfaces(objs, max_objs, textured_objs))
		return (false);
	return (true);
}
