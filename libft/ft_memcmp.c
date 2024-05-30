/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:47:41 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/09 17:24:26 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*data1;
	unsigned char	*data2;

	data1 = (unsigned char *) s1;
	data2 = (unsigned char *) s2;
	while (n--)
	{
		if (*data1 != *data2)
			return (*data1 - *data2);
		data1++;
		data2++;
	}
	return (0);
}
