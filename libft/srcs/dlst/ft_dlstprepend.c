/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstprepend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <mdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 22:23:18 by mdeville          #+#    #+#             */
/*   Updated: 2018/06/06 19:11:26 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "dlst.h"
#include <stdlib.h>

void	ft_dlstprepend(t_dlist **alst, t_dlist *new)
{
	if (!alst)
		return ;
	if (!new)
	{
		ft_printf("Allocation Failure\n");
		exit(EXIT_FAILURE);
	}
	new->next = *alst;
	if (*alst)
	{
		new->prev = (*alst)->prev;
		if ((*alst)->prev)
			(*alst)->prev->next = new;
		(*alst)->prev = new;
	}
	else
		new->prev = NULL;
	*alst = new;
}
