/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:48:16 by malexand          #+#    #+#             */
/*   Updated: 2017/10/15 22:04:35 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	putpxl(SDL_Surface *surface, int x, int y, Uint32 pixel)
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

Uint32 getpxl(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
/*
** Convert if getpxl return another value
** tab_color: [0] = red ; [1] = green ; [2] = blue ; [3] = alpha
*/

int		convert_Uint32_to_int(Uint32 pixel, SDL_PixelFormat *fmt)
{
	Uint8		*tab_color;
	int			count;
	int			color;

	count = 0x00000000;
	tab_color = (Uint8 *)malloc(sizeof(Uint8) * 4);
	SDL_GetRGBA(pixel, fmt, &tab_color[0], &tab_color[1], &tab_color[2], &tab_color[3]);
	color = RGB(tab_color[0], tab_color[1], tab_color[2]);
	ft_putnbr(color);
	ft_putendl("");
	return color;
}
