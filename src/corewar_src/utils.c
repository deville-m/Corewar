/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:20:10 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/30 17:54:41 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <libft.h>
#include <colors.h>
#include <commons.h>

/*
** @desc dump memory to stdout
** @return nil
*/

void			dump_memory(const unsigned char *memory,
						const unsigned char *ownership,
						size_t i)
{
	(void)ownership;
	while (i < MEM_SIZE)
	{
		if ((i + 1) != MEM_SIZE && (i % 64) == 0)
			ft_printf("\n0x0%.3x : ", i);
		else if ((i % 64) == 0)
			ft_putchar('\n');
		ft_printf("%.2x ", memory[i]);
		i++;
	}
	ft_putchar('\n');
}
