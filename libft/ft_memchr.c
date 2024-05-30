/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:43:22 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/17 10:41:45 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*chr;
	unsigned char	ch;

	ch = (unsigned char) c;
	chr = (unsigned char *)s;
	while (n--)
	{
		if (*chr == ch)
			return ((void *) chr);
		chr++;
	}
	return (NULL);
}
