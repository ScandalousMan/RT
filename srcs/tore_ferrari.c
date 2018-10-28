#include "rt.h"

double sgn(double z)
{
	if (z > 0.0f)
		return (1.0f);
	else if (z < 0.0f)
		return (-1.0f);
	return (0.0f);
}

double uv(double sg, double del, double q)
{
	double	z;

	z = -q / 2.0f + sg * sqrt(del);
	return (sgn(z) * pow(ft_absdbl(z), 1.0f / 3.0f));
}

double sub_ferrari(double u, double A, double z, double bs)
{
	double	x[4];
	double 	d[2];
	double	res;
	double	uma;

	uma = u - A;
	x[0] = -1.0f;
	x[1] = -1.0f;
	x[2] = -1.0f;
	x[3] = -1.0f;
	res = -1.0f;
	d[0] = uma - 4.0f * (z * sqrt(uma) + u / 2.0f);
	d[1] = uma - 4.0f * (-z * sqrt(uma) + u / 2.0f);
	if (d[0] >= 0)
	{
		x[0] = (sqrt(uma) + sqrt(d[0])) / 2.0f - bs;
		x[1] = (sqrt(uma) - sqrt(d[0])) / 2.0f - bs;
	}
	if (d[1] >= 0)
	{
		x[2] = (sqrt(uma) + sqrt(d[1])) / 2.0f - bs;
		x[3] = (sqrt(uma) - sqrt(d[1])) / 2.0f - bs;
	}
	if (x[0] > 0)
		res = x[0];
	if (x[1] > 0 && (x[1] < res || res < 0))
		res = x[1];
	if (x[2] > 0 && (x[2] < res || res < 0))
		res = x[2];
	if (x[3] > 0 && (x[3] < res || res < 0))
		res = x[3];	

	return (res);
}

double	ferrari(double a, double b, double c, double d, double e)
{
	double	A;
	double	B;
	double	C;
	double	x[3];

	if (!a)
		return (-1.0f);
	A = -3.0f * b * b / 8.0f / a / a + c / a;
	B = ft_pow(b / 2.0f, 3.0f) / a / a / a - 0.5 * b * c / a / a + d / a;
	C = -3.0f * ft_pow(b / 4.0f / a, 4.0f) + c * ft_pow(b / 4.0f, 2.0f) / a / a / a -
		0.25 * b * d / a / a + e / a;

	if (B == 0.0)
		return (-1.0f);

	double	p;
	double	q;
	double	del;
	double	u;
	double	bs;

	double	kos;
	double	r;
	double	alpha;

	bs = b / 4.0f / a;
	a = 1.0;
	b = -A;
	c = -4.0f * C;
	d = 4.0f * A * C - B * B;

	p = c / a - b * b / 3.0f / a / a;
	q = b * b * b / a / a / a / 13.5 + d / a - b * c / 3.0f / a / a;
	del = q * q / 4.0f + p * p * p / 27.0f;

	if (del <= 0.0f)
	{
		if (p)
		{
			kos = -q / 2.0f / sqrt(-p * p * p / 27.0f);
			r = sqrt(-p / 3.0f);
		}
		else
		{
			kos = 0.0f;
			r = 0.0f;
		}
		if (ft_absdbl(kos) - 1.0f == 0.0f)
			alpha = -1.0f * M_PI * (kos - 1.0f) / 2.0f;
		else
			alpha=acos(kos);

		x[0]= 2.0f * r - b / 3.0f / a;
		x[1]= 2.0f * r * cos((alpha + 2.0f * M_PI) / 3.0f) - b / 3.0f / a;
		x[2]= 2.0f * r * cos((alpha + 4.0f * M_PI) / 3.0f) - b / 3.0f / a;

		if (!r)
			u = x[0];
		else if (x[0] > A)
			u = x[0];
		else if (x[2] > A)
			u = x[2];
		else
			u = x[1];
	}
	else
		u = uv(1.0f, del, q) + uv(-1.0f, del, q) - b / 3.0f / a;

	double	res;

	res = sub_ferrari(u, A, B / 2.0f / (u - A), bs);
	return (res);
}


