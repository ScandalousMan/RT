/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:48:16 by malexand          #+#    #+#             */
/*   Updated: 2017/09/26 16:48:26 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

void	putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint8	*p;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x *
		surface->format->BytesPerPixel;
	if (surface->format->BytesPerPixel == 1)
		*p = pixel;
	else if (surface->format->BytesPerPixel == 2)
		*(Uint16 *)p = pixel;
	else if (surface->format->BytesPerPixel == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xFF;
			p[1] = (pixel >> 8) & 0xFF;
			p[2] = pixel & 0xFF;
		}
		else
		{
			p[0] = pixel & 0xFF;
			p[1] = (pixel >> 8) & 0xFF;
			p[2] = (pixel >> 16) & 0xFF;
		}
	}
	else if (surface->format->BytesPerPixel == 4)
		*(Uint32 *)p = pixel;
}
