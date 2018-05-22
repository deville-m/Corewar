/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:01:46 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/22 16:01:52 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	trad_input(unsigned char *src, unsigned int *dest, int len)
{
	int	i;

	*dest = 0;
	i = 0;
	while (i < len)
	{
		*dest |= src[i];
		if (i < len - 1)
			*dest <<= 8;
		i += 1;
	}
}
