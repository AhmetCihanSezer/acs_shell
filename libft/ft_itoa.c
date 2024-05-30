/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:19:18 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/09 16:43:27 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_counter(int n)
{
	int	i;

	i = 0;
	if (!n)
		i = 1;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	digit;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digit = digit_counter(n);
	str = (char *) malloc(sizeof(char) * (digit + 1));
	if (!str)
		return (NULL);
	str[digit] = 0;
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	while (n > 9)
	{
		str[digit - 1] = (n % 10) + '0'; 
		n /= 10;
		digit--;
	}
	str[digit - 1] = n + '0';
	return (str);
}
