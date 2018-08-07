#include "rt.h"

int			define_sign(double z)
{
	if (z > 0.0)
		return 1;
	else if (z < 0.0)
		return -1;
	return 0;
}

double	uv(int sign, double q, double delta)
{
	double z;

	z = q / -2.0 + (double)sign * sqrt(delta);
	return (define_sign(z) * pow(ABS(z),1.0 / 3.0));
}

double	cardan_solver(double a, double b, double c, double d)
{
	double	p;
	double	q;
	double	delta;
	double	kos;
	double	r;
	double	alpha;
	double	res;
	double	tmp_res;
	double	k;

	if (a == 0.0)
		return second_level(b, c, d);

	p = c / a  - b * b / 3.0 / a / a;
	q = 2.0 * b * b * b / 27.0 / a / a / a + d / a - b * c / 3.0 / a / a;

	if (p == 0.0)
		return pow(-1.0 * q, 1.0 / 3.0);
	if (q == 0.0)
	{
		if (p < 0.0)
			return sqrt(p);
		else
			return (0.0);
	}

	delta = q * q / 4.0 + p * p * p / 27.0;
	if (delta > 0.0)
		return pow(q / -2.0 + sqrt(delta), 1.0 / 3.0) + pow(q / -2.0 - sqrt(delta), 1.0 / 3.0);
	else if (delta < 0.0)
	{
		kos = q / -2.0 / sqrt(p * p * p / -27.0);
		r = sqrt(p / -3.0);
		alpha = acos(kos);

		k = 0;
		res = -1.0;
		while (k < 3)
		{
			tmp_res = 2.0 * r * cos((alpha + 2.0 * k * M_PI) / 3.0) - b / 3.0 / a;
			if (res < 0.0 || tmp_res < res)
				res = tmp_res;
			k++;
		}
		return (res);
	}
	else
		return (uv(1, q, delta) + uv(-1, q, delta) - b / 4.0 / a);
}

double	ferrari(double a, double b, double c, double d, double e)
{
	double A;
	double B;
	double C;

	if (a == 0.0)
		return (0.0);

	A = -3.0 * b * b / 8.0 / a / a + c / a;
	B = ft_pow(b / 2.0, 3) / a / a / a - 0.5 * b * c / a / a + d / a;
	C = -3.0 * ft_pow(b / 4.0 / a, 4) + c * ft_pow(b / 4.0, 2) / a / a / a - 0.25 * b * d / a / a + e / a;
	if (B == 0.0)
		return sqrt(second_level(1.0, A, C));

	return B / 2.0 / (cardan_solver(1.0, -1.0 * A, -4.0 * C, 4.0 * A * C - B * B) - A);
}
