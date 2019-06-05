/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sdl_load_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:58:23 by tmaluh            #+#    #+#             */
/*   Updated: 2019/06/05 14:24:11 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static Uint32	*add_free_helper(t_helper *restrict const h, const Uint32 *ret)
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

static Uint32	*add_copy_data_to_objects(t_figure *restrict const objs,
							const size_t max_objs,
							t_helper *restrict const h)
{
	Uint32					*out;
	const Uint32 *restrict	curr_tex;
	size_t					i;
	size_t					j;
	Dot						p;
	Dot						o;

	j = ~0L;
	i = ~0L;
	if (!(out = malloc(sizeof(Uint32) * (h->max_width * h->summ_height))))
		return (add_free_helper(h, NULL));
	while (max_objs > ++i)
		if (objs[i].texture)
		{
			curr_tex = (Uint32*)h->tex_surf[++j]->pixels;
			objs[i].spos = h->spos[j];
			objs[i].epos = h->epos[j];
			p.y = objs[i].spos.y;
			o.y = ~0L;
			while (h->tex_surf[j]->h > o.y && objs[i].epos.y > p.y
			&& (o.x = ~0L))
			{
				p.x = objs[i].spos.x;
				while (objs[i].epos.x > p.x && h->tex_surf[j]->w > ++o.x)
				{
					out[p.y * h->max_width + p.x] =
						curr_tex[o.y * h->tex_surf[j]->w + o.x];
					++p.x;
				}
				++p.y;
			}
		}
	return (add_free_helper(h, out));
}

static Uint32	*add_prepare_texture_map(t_figure *restrict const objs,
							const size_t max_objs,
							t_helper *restrict const h)
{
	size_t	i;
	size_t	j;

	i = ~0L;
	j = ~0L;
	if (!(h->spos = (Dot*)malloc(sizeof(Dot) * h->textured_objs)))
		return (add_free_helper(h, NULL));
	if (!(h->epos = (Dot*)malloc(sizeof(Dot) * h->textured_objs)))
		return (add_free_helper(h, NULL));
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
	return (add_copy_data_to_objects(objs, max_objs, h));
}

static Uint32	*add_load_texture_surfaces(t_figure *restrict const objs,
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
		return (add_free_helper(h, NULL));
	ft_bzero(h->tex_surf, sizeof(SDL_Surface) * h->textured_objs);
	while (max_objs > ++i)
		if (objs[i].texture)
		{
			++j;
			if (!(h->tex_surf[j] =
			sdl_load_image(objs[i].texture, format, h->tex_surf[j])))
				return (add_free_helper(h, NULL));
			if (h->tex_surf[j]->w > max_width)
				max_width = h->tex_surf[j]->w;
			summ_height += h->tex_surf[j]->h;
		}
	return (add_prepare_texture_map(objs, max_objs, h));
}

Uint32			*rt_sdl_load_textures(t_figure *restrict const objs,
							const size_t max_objs,
							const SDL_PixelFormat *format)
{
	size_t		i;
	t_helper	h;

	i = ~0L;
	ft_bzero(&h, sizeof(t_helper));
	while (max_objs > ++i)
		if (objs[i].texture)
			++h.textured_objs;
	if (h.textured_objs)
		return (add_load_texture_surfaces(objs, max_objs, &h, format));
	return (NULL);
}
