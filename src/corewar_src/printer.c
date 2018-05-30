/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:23:36 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/30 09:16:45 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc dump to stdout players headers
**       beforee running thread
** @param arena current arena struct
** @return nil
*/

void				print_player_headers(t_arena *arena,
								size_t i)
{
	uint32_t x;

	ft_printf("Introducing contestants...\n");
	while (i < arena->np)
	{
		x = arena->players[i].header.prog_size;
		swap_endian(&x, sizeof(x));
		ft_printf("* Player %zu, weighing %u bytes, \"%s\" !\n",
			arena->players[i].id, x,
			arena->players[i].header.comment);
		i++;
	}
}

/*
** @desc dump to stdout players headers
**       beforee running thread
** @param arena current arena struct
** @return nil
*/

void				print_winner(t_arena *arena,
						size_t i)
{
	unsigned int	maxi;
	size_t			aref;

	maxi = 0;
	aref = 0;
	while (i < arena->np)
	{
		if (arena->players[i].last_live > maxi)
		{
			aref = i;
			maxi = arena->players[i].last_live;
		}
		i++;
	}
	ft_printf("Contestants %zu, \"%s\", \"%s\", has won !\n",
		arena->players[aref].id,
		arena->players[aref].header.prog_name,
		arena->players[aref].header.comment);
}
