/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:57:45 by yenyilma          #+#    #+#             */
/*   Updated: 2024/11/14 00:57:46 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lstlen;

	if (!lst)
		return (0);
	lstlen = 1;
	while (lst->next)
	{
		lst = lst->next;
		lstlen++;
	}
	return (lstlen);
}
