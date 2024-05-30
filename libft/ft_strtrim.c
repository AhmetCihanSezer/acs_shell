/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:31:43 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/17 10:47:50 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_contain(char const chr, char const *set)
{
	while (*set)
		if (*set++ == chr)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	fin_len;
	int	len;

	if (!s1)
		return (NULL);
	while (*s1 && is_contain(*s1, set))
		s1++;
	i = 0;
	len = ft_strlen(s1);
	if (len <= 0)
		return (ft_strdup(""));
	while (is_contain(s1[len - i - 1], set))
		i++;
	fin_len = len - i;
	return (ft_substr(s1, 0, fin_len));
}
