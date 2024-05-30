/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:51 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/17 10:38:47 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;
	int				i;
	int				total;

	total = count * size;
	result = (unsigned char *)malloc(total);
	if (!result)
		return (NULL);
	i = 0;
	while (i < total)
		result[i++] = 0;
	return ((void *)result);
}
