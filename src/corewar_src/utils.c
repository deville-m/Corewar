/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:20:10 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/24 10:16:34 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <libft.h>
#include <colors.h>
#include <commons.h>

/*
** Retrieve ad-hoc colors depending
** of the player cusor.
*/

char			*jcolors(unsigned char owner, t_bool bold)
{
	if (owner == 0xFF)
		return ((bold) ? LIGHTGREEN : GREEN);
	else if (owner == 0xFE)
		return ((bold) ? LIGHTBLUE : BLUE);
	else if (owner == 0xFD)
		return ((bold) ? LIGHTRED : RED);
	else if (owner == 0xFC)
		return ((bold) ? LIGHTYELLOW : YELLOW);
	return ((bold) ? LIGHTBLACK : BLACK);
}

/*
** @desc dump memory to stdout
** @return nil
*/

void			dump_memory(const unsigned char *memory,
						const unsigned char *ownership,
						size_t i)
{
	ft_printf("Dumping memory of size: %d\n", MEM_SIZE);
	while (i < MEM_SIZE)
	{
		if (memory[i] == 0xff)
			ft_putstr(jcolors(ownership[i], FALSE));
		else if (memory[i] == 0x00)
			ft_putstr(jcolors(ownership[i], FALSE));
		else
			ft_putstr(jcolors(ownership[i], TRUE));
		if ((i % 50) == 0)
			ft_putchar('\n');
		ft_printf("%.2x ", memory[i]);
		i++;
	}
	ft_putchar('\n');
	ft_putstr(RESET);
}

/*
** @desc Dump player exec to stdout
** @return nil
*/

void			dump_player_exec(t_arena *arena)
{
	size_t		p;
	size_t		i;

	p = 0;
	while (p < arena->np)
	{
		i = 0;
		ft_printf("\nSize of player[%zu]: %u\n", p,
			arena->players[p].header.prog_size);
		while (i < arena->players[p].header.prog_size)
		{
			if (arena->players[p].exec[i] != 0x0)
				ft_putstr(LIGHTRED);
			else
				ft_putstr(BLACK);
			if ((i % 15) == 0)
				ft_putchar('\n');
			ft_printf("\\x%.2x ", arena->players[p].exec[i]);
			i++;
		}
		ft_printf("\n%s", RESET);
		p++;
	}
}
