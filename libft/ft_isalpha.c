/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalpha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:22:04 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/04 11:34:07 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
		return (1);
	return (0);
}