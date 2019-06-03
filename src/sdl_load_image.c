/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_load_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 15:20:18 by tmaluh            #+#    #+#             */
/*   Updated: 2019/06/03 16:09:29 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "../SDL2_image.framework/Headers/SDL_image.h"

SDL_Surface	*sdl_load_image(const char *const path,
							const SDL_PixelFormat *format,
							SDL_Surface *dst)
{
	SDL_Surface	*temp;

	temp = NULL;
	if (!(temp = IMG_Load(path)))
	{
		ft_putendl_fd(IMG_GetError(), STDERR_FILENO);
		return (NULL);
	}
	else
	{
		if (!(dst = SDL_ConvertSurface(temp, format, 0)))
		{
			ft_putendl_fd(SDL_GetError(), STDERR_FILENO);
			return (NULL);
		}
		SDL_FreeSurface(temp);
	}
	return (dst);
}
