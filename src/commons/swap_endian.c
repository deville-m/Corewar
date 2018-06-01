/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_endian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:32:25 by mdeville          #+#    #+#             */
/*   Updated: 2018/06/01 18:29:57 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <commons.h>

void swap_endian(void *data, size_t size)
{
	char	tmpdata;
	char	*tmp;
	size_t	i;

	if (!data)
		return ;
	tmp = (char *)data;
	i = 0;
	--size;
	while (i < size)
	{
		tmpdata = tmp[i];
		tmp[i] = tmp[size];
		tmp[size] = tmpdata;
		++i;
		--size;
	}
}
