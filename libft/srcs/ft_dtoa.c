#include "libft.h"

char	*ft_decimal(double d, int index)
{
	int count;
	char *str;

	count = 1;
	if (!(str = (char *)malloc((index + 2 * sizeof(char)))))
		return NULL;
	str[0] = '.';
	str[index + 1] = '\0';
	d -= trunc(d);
	while (d != FLT_MIN && count < index + 1)
	{
		d = d * 10;
		str[count] = trunc(d) + '0';
		d -= trunc(d);
		count++;
	}
	return str;
}

char 	*ft_dtoa(double d, int index)
{
	char	*start;
	char	*end;

	if (index <= 0 || index > 16)
		return (NULL);
	if (!(start = ft_itoa((int)d)))
		return NULL;
	if (!(end = ft_decimal(d, index)))
		return NULL;
	return ft_strjoin_free(start, end);
}
