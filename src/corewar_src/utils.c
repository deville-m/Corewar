/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:20:10 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/15 10:46:06 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <libft.h>
#include <colors.h>

/*
** @desc print usage and exit;
** @return Nil (exit)
*/

void	usage(void)
{
	ft_printf("Usage: ./corewar [-d nbr_cycles] ");
	ft_printf("[[-n number] champion1.cor] ...\n");
	exit(EXIT_FAILURE);
}

/*
** @desc dump memory to stdout
** @return nil
*/

void	dump_memory(const unsigned char *memory,
					size_t i)
{
	ft_printf("Dumping memory of size: %d\n", MEM_SIZE);
	while (i < MEM_SIZE)
	{
		if (memory[i] != 0xff)
			ft_putstr(BOLDGREEN);
		else
			ft_putstr(BLACK);
		if ((i % 40) == 0)
			ft_putchar('\n');
		ft_printf("%.2x ", memory[i]);
		i++;
	}
}
