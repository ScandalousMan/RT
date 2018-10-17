#include "libft.h"

int ft_decimal_len(double d)
{
	int count;

	count = 0;
	while (d > FLT_MIN && count < 32)
	{
		d = (d - (int)(d + 0.1)) * 10;
		d -= trunc(d);
		count++;
	}
	return count;
}

int ft_dbllen(double d, int index)
{
	double tmp_dbl;
	int len;

	len = 1;
	if (d < 0.0)
	{
		d = -d;
		len++;
	}
	tmp_dbl = trunc(d);
	d -= tmp_dbl;
	while (tmp_dbl < -9.0 || tmp_dbl > 9.0)
	{
		tmp_dbl /= 10;
		len++;
	}
	if (index != 0 && index > 0 && index < 32)
		len += index;
	else
		len += ft_decimal_len(d);
	return (len);
}