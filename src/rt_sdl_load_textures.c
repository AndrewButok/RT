/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sdl_load_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:58:23 by tmaluh            #+#    #+#             */
/*   Updated: 2019/06/03 19:31:05 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	add_prepare_texture_map(t_figure *restrict const objs,
							const size_t max_objs,
							SDL_Surface *restrict tex_surf[],
							const size_t summ_height,
							const size_t max_width,
							const size_t texured_objs)
{
	Dot		*spos;
	Dot		*epos;
	size_t	i;
	size_t	j;

	i = ~0L;
	j = ~0L;
	if (!(spos = (Dot*)malloc(sizeof(Dot) * texured_objs)))
		return (false);
	if (!(epos = (Dot*)malloc(sizeof(Dot) * texured_objs)))
	{
		free(spos);
		return (false);
	}
	while (max_objs > ++i)
	{
		objs[i].spos = (Dot){-1, -1};
		if (objs[i].texture)
		{
			++j;
			ft_bzero(&spos[j], sizeof(Dot));
			ft_bzero(&epos[j], sizeof(Dot));
			spos[j].y += epos[j - 1].y;
			epos[j].x = tex_surf[j]->w;
			epos[j].y = spos[j].y + tex_surf[j]->h;
		}
	}
	j = ~0L;
	i = ~0L;
	while (max_objs > ++i)
		if (objs[i].texture)
		{
			++j;
			objs[i].spos = spos[j];
			objs[i].epos = epos[j];
		}
	free(spos);
	free(epos);
	return (true);
}

static bool	add_load_texture_surfaces(t_figure *restrict const objs,
							const size_t max_objs,
							const size_t textured_objs,
							const SDL_PixelFormat *format)
{
	SDL_Surface	*tex_surf[textured_objs];
	size_t		i;
	size_t		j;
	size_t		max_width;
	size_t		summ_height;

	i = ~0L;
	j = ~0L;
	max_width = 0;
	summ_height = 0;
	while (max_objs > ++i)
		if (objs[i].texture)
		{
			++j;
			if (!(tex_surf[j] =
			sdl_load_image(objs[i].texture, format, tex_surf[j])))
				return (false);
			if (tex_surf[j]->w > max_width)
				max_width = tex_surf[j]->w;
			summ_height += tex_surf[j]->h;
		}
	return (add_prepare_texture_map(objs, max_objs, tex_surf,
		summ_height, max_width, textured_objs));
}

bool		rt_sdl_load_textures(t_figure *restrict const objs,
							const size_t max_objs,
							const SDL_PixelFormat *format)
{
	size_t		i;
	size_t		textured_objs;

	i = ~0L;
	textured_objs = 0;
	while (max_objs > ++i)
		if (objs[i].texture)
			++textured_objs;
	if (textured_objs)
		return (add_load_texture_surfaces(objs, max_objs,
			textured_objs, format));
	return (true);
}
