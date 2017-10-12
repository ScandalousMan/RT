/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:48:16 by malexand          #+#    #+#             */
/*   Updated: 2017/10/12 11:12:12 by malexand         ###   ########.fr       */
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

Uint32	getpxl(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
	if (x < 0 || y < 0 || x > WINDOW_SDL_WIDTH || y > WINDOW_SDL_HEIGHT / NB_THREAD)
		return 0;
	if (bpp == 1)
		return *p;
	else if (bpp == 2)
		return *(Uint16 *)p;
	else if (bpp == 3)
	{
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
	}
	else if (bpp == 4)
		return *(Uint32 *)p;
	else
		return 0;
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

	count = 0;
	// color = 0x00000000;
	tab_color = (Uint8 *)malloc(sizeof(Uint8) * 4);
	SDL_GetRGBA(pixel, fmt, &tab_color[0], &tab_color[1], &tab_color[2], &tab_color[3]);
	color = tab_color[0] + 256 * tab_color[1] + 256 * 256 * tab_color[2];
	ft_putnbr(tab_color[0]);
	ft_putstr(", ");
	ft_putnbr(tab_color[1]);
	ft_putstr(", ");
	ft_putnbr(tab_color[2]);
	ft_putstr(", ");
	ft_putnbr(tab_color[3]);
	ft_putstr(")\n");
	// color += (int)(tab_color[0] & 0xFF000000);
	// color += (int)(tab_color[1] & 0x00FF0000);
	// color += (int)(tab_color[2] & 0x0000FF00);
	// color += (int)(tab_color[3] & 0x000000FF);
	return color;
}
