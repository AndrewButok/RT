/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sdl_load_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:58:23 by tmaluh            #+#    #+#             */
/*   Updated: 2019/06/04 18:26:34 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool		add_free_helper(t_helper *restrict const h, const bool ret)
{
	size_t	i;

	i = ~0L;
	if (h->tex_surf)
	{
		while (h->textured_objs > ++i)
			FREE(h->tex_surf[i], SDL_FreeSurface);
		FREE(h->tex_surf, free);
	}
	FREE(h->spos, free);
	FREE(h->epos, free);
	return (ret);
}

static bool		add_copy_to_poses_objects(t_figure *restrict const objs,
							const size_t max_objs,
							t_helper *restrict const h)
{
	size_t	i;
	size_t	j;

	j = ~0L;
	i = ~0L;
	while (max_objs > ++i)
		if (objs[i].texture)
		{
			objs[i].spos = h->spos[++j];
			objs[i].epos = h->epos[j];
		}
	return (add_free_helper(h, true));
}

static bool		add_prepare_texture_map(t_figure *restrict const objs,
							const size_t max_objs,
							t_helper *restrict const h)
{
	size_t	i;
	size_t	j;

	i = ~0L;
	j = ~0L;
	if (!(h->spos = (Dot*)malloc(sizeof(Dot) * h->textured_objs)))
		return (add_free_helper(h, false));
	if (!(h->epos = (Dot*)malloc(sizeof(Dot) * h->textured_objs)))
		return (add_free_helper(h, false));
	while (max_objs > ++i)
	{
		objs[i].spos = (Dot){-1, -1};
		if (objs[i].texture)
		{
			++j;
			ft_bzero(&h->spos[j], sizeof(Dot));
			ft_bzero(&h->epos[j], sizeof(Dot));
			h->spos[j].y += h->epos[j - 1].y;
			h->epos[j].x = h->tex_surf[j]->w;
			h->epos[j].y = h->spos[j].y + h->tex_surf[j]->h;
		}
	}
	return (add_copy_to_poses_objects(objs, max_objs, h));
}

static bool		add_load_texture_surfaces(t_figure *restrict const objs,
							const size_t max_objs,
							t_helper *restrict const h,
							const SDL_PixelFormat *format)
{
	size_t		i;
	size_t		j;
	size_t		max_width;
	size_t		summ_height;

	i = ~0L;
	j = ~0L;
	max_width = 0;
	summ_height = 0;
	if (!(h->tex_surf = malloc(sizeof(SDL_Surface) * h->textured_objs)))
		return (add_free_helper(h, false));
	ft_bzero(h->tex_surf, sizeof(SDL_Surface) * h->textured_objs);
	while (max_objs > ++i)
		if (objs[i].texture)
		{
			++j;
			if (!(h->tex_surf[j] =
			sdl_load_image(objs[i].texture, format, h->tex_surf[j])))
				return (add_free_helper(h, false));
			if (h->tex_surf[j]->w > max_width)
				max_width = h->tex_surf[j]->w;
			summ_height += h->tex_surf[j]->h;
		}
	return (add_prepare_texture_map(objs, max_objs, h));
}

bool			rt_sdl_load_textures(t_figure *restrict const objs,
							const size_t max_objs,
							const SDL_PixelFormat *format,
							Uint32 *restrict tex_pxls)
{
	size_t		i;
	t_helper	h;

	i = ~0L;
	ft_bzero(&h, sizeof(t_helper));
	h.pxls = tex_pxls
		= NULL;
	while (max_objs > ++i)
		if (objs[i].texture)
			++h.textured_objs;
	if (h.textured_objs)
		return (add_load_texture_surfaces(objs, max_objs, &h, format));
	return (true);
}
