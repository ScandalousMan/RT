#include "rt.h"


double smoothNoise(double x, double y, t_param *param)
{
	double	fractX;
	double	fractY;
	int 		x1;
	int 		x2;
	int 		y1;
	int 		y2;
	double	value;

  //get fractional part of x and y
  fractX = x - floor(x);
  fractY = y - floor(y);

	//wrap around
	x1 = ((int)(floor(x) + NOISE_SIZE)) % NOISE_SIZE;
	y1 = ((int)(floor(y) + NOISE_SIZE)) % NOISE_SIZE;

	//neighbor values
	x2 = (x1 + NOISE_SIZE - 1) % NOISE_SIZE;
	y2 = (y1 + NOISE_SIZE - 1) % NOISE_SIZE;

	//smooth the noise with bilinear interpolation
	value = 0.0;
	value += fractX     * fractY     * param->perlin_noise[y1][x1];
	value += (1 - fractX) * fractY     * param->perlin_noise[y1][x2];
	value += fractX     * (1 - fractY) * param->perlin_noise[y2][x1];
	value += (1 - fractX) * (1 - fractY) * param->perlin_noise[y2][x2];

  return value;
}

double turbulence(double x, double y, double size, t_param *param)
{
  double	value = 0.0;
  double	initialSize = size;

  while (size >= 1)
  {
    value += smoothNoise(x / size, y / size, param) * size;
    size /= 2.0;
  }

  return(128.0 * value / initialSize);
}

double	marble_ratio(double u, double v, double size, t_param *param)
{
	double xPeriod;
	double yPeriod;

	xPeriod = 5.0;
	yPeriod = 10.0;
	return ft_absdbl(M_PI * (u * xPeriod / (double)NOISE_SIZE +
		v * yPeriod / (double)NOISE_SIZE +
		TURB_POWER * turbulence(u, v, size, param) / 256.0));
}
