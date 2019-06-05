/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_figure_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:12:00 by abutok            #+#    #+#             */
/*   Updated: 2019/06/03 14:49:30 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_figure_texture(t_figure *figure, JSON_Object *obj,
		SDL_PixelFormat *pf)
{
	char		*filename;
	SDL_Surface	*s;

	figure->texture = NULL;
	filename = NULL;
	s = NULL;
	if (json_object_has_value_of_type(obj, "texture", JSONString))
	{
		filename = (char*)json_object_get_string(obj, "texture");
		s = sdl_load_image(filename, pf, s);
		if (s != NULL)
		{
			figure->texture = (int*)malloc(sizeof(int) * s->w * s->h);
			figure->texture = ft_memcpy(figure->texture, s->pixels,
										sizeof(int) * s->w * s->h);
			figure->t_size.x = s->w;
			figure->t_size.y = s->h;
			SDL_FreeSurface(s);
		}
	}
}
