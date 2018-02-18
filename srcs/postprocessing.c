#include "rt.h"

int		greyscaler(int color)
{
	return (int)(MIN(MIN(color & 0xFF, (color >> 8) & 0xFF), (color >> 16) & 0xFF) +
		MAX(MAX(color & 0xFF, (color >> 8) & 0xFF), (color >> 16) & 0xFF)) / 2 * (1 + 256 + 256 * 256);
}

void	greyscale(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], greyscaler(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

int		sepiacer(int color)
{

	return (
		(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.393 + (float)((color >> 8) & 0xFF) * 0.769 + (float)((color) & 0xFF) * 0.189)) << 16) |
		(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.349 + (float)((color >> 8) & 0xFF) * 0.686 + (float)((color) & 0xFF) * 0.168)) << 8) |
		(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.272 + (float)((color >> 8) & 0xFF) * 0.534 + (float)((color) & 0xFF) * 0.131)))
	);
}

void	sepia(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], sepiacer(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

int		cartooner(int color)
{
	return (((int)((color & 0xFF) / CARTOON_FACTOR) * CARTOON_FACTOR) |
		((int)(((color >> 8) & 0xFF) / CARTOON_FACTOR) * CARTOON_FACTOR << 8) |
		((int)(((color >> 16) & 0xFF) / CARTOON_FACTOR) * CARTOON_FACTOR << 16));
}

void	cartoon(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], cartooner(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

void	blur(t_param *param)
{
	double 	res[3];
	int			rs;
	double	wsum;
	double	wght;
	double	dsq;
	int			x;
	int			y;
	int 		ix;
	int 		iy;

  rs = (int)ceil((double)BLUR_RADIUS * 2.57);
  param->i[0] = 0;
  while (param->i[0] < WINDOW_SDL_HEIGHT)
  {
  	param->i[1] = 0;
  	while (param->i[1] < WINDOW_SDL_WIDTH)
  	{
  		res[0] = 0;
  		res[1] = 0;
  		res[2] = 0;
  		wsum = 0.0;
  		iy = param->i[0] - rs;
  		while (iy < param->i[0] + rs + 1)
  		{
  			ix = param->i[1] - rs;
  			while (ix < param->i[1] + rs + 1)
  			{
  				x = ft_min(WINDOW_SDL_WIDTH - 1, ft_max(0, ix));
  				y = ft_min(WINDOW_SDL_HEIGHT - 1, ft_max(0, iy));
  				dsq = (double)((param->i[1] - ix) * (ix - param->i[1]) + (iy - param->i[0]) * (param->i[0] - iy));
  				wght = exp(dsq / (double)(2 * BLUR_RADIUS * BLUR_RADIUS)) / M_PI / (double)(2 * BLUR_RADIUS * BLUR_RADIUS);
  				res[0] += ((param->pxl_infos[y][x]->col >> 16) & 0xFF) * wght;
  				res[1] += ((param->pxl_infos[y][x]->col >> 8) & 0xFF) * wght;
  				res[2] += ((param->pxl_infos[y][x]->col) & 0xFF) * wght;
  				wsum += wght;
  				ix++;
  			}
  			iy++;
  		}
  		res[0] = res[0] / wsum;
  		res[1] = res[1] / wsum;
  		res[2] = res[2] / wsum;
			putpxl(param, param->i[0], param->i[1], rgb_color((unsigned char)res[0], (unsigned char)res[1], (unsigned char)res[2]));

  		param->i[1]++;
  	}
  	param->i[0]++;
  }

  // for(var i=0; i<h; i++)
  //     for(var j=0; j<w; j++) {
  //         var val = 0, wsum = 0;
  //         for(var iy = i-rs; iy<i+rs+1; iy++)
  //             for(var ix = j-rs; ix<j+rs+1; ix++) {
  //                 var x = Math.min(w-1, Math.max(0, ix));
  //                 var y = Math.min(h-1, Math.max(0, iy));
  //                 var dsq = (ix-j)*(ix-j)+(iy-i)*(iy-i);
  //                 var wght = Math.exp( -dsq / (2*r*r) ) / (Math.PI*2*r*r);
  //                 val += scl[y*w+x] * wght;  wsum += wght;
  //             }
  //         tcl[i*w+j] = Math.round(val/wsum);            
  //     }
}
