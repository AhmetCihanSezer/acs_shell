/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:29:51 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/17 10:47:19 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*result;
	unsigned char	ch;

	ch = (unsigned char) c;
	result = NULL;
	while (*s)
	{
		if (*s == ch)
			result = (char *)s;
		s++;
	}
	if (!ch)
		return ((char *) s);
	return (result);
}
