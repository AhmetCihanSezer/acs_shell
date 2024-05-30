/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsezer <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:36:07 by ahsezer           #+#    #+#             */
/*   Updated: 2023/07/09 11:42:04 by ahsezer          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;
	t_list	*last;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		temp = *lst;
		last = ft_lstlast(temp);
		last->next = new;
	}
}
