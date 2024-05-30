/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:15:31 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/09 15:27:18 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;

	dest = (char *) dst;
	source = (char *) src;
	if (dst < src)
	{
		while (len--)
		{
			*dest = *source;
			dest++;
			source++;
		}
	}
	else if (dst > src)
	{
		while (len--)
			dest[len] = source[len];
	}
	return (dst);
}
