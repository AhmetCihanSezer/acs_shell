/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:04:21 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/17 10:46:44 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *neddle, size_t len)
{
	int	i;
	int	j;

	if (!*neddle)
		return ((char *) haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == neddle[j] && haystack[i + j] && i + j < len)
			j++;
		if (!neddle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
