/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:23:36 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 19:37:03 by ctrouill         ###   ########.fr       */
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
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
			i + 1,
			x,
			arena->players[i].header.prog_name,
			arena->players[i].header.comment);
		i++;
	}
}

static void			audio_winner(char *user, t_arena *arena)
{
	char			mes[400];

	if (arena->opts->audio)
	{
		ft_memset(mes, 0x00, 400);
		ft_strcat(mes, "And the winner is: ");
		ft_strcat(mes, user);
		ft_strcat(mes, " !");
		ft_strcat(mes, "Congratulations !&");
		play_voice(mes);
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
	audio_winner(arena->players[aref].header.prog_name, arena);
}

/*
** @desc dump to stdout players headers
**       beforee running thread
** @param arena current arena struct
** @return nil
*/

void				print_winner_gfx(t_arena *arena,
						size_t i, t_scene *scn, size_t aref)
{
	unsigned int	maxi;

	maxi = 0;
	wclear(scn->sidebar);
	timeout(-1);
	wattron(scn->sidebar, A_BLINK);
	wrefresh(scn->sidebar);
	while (i < arena->np)
	{
		if (arena->players[i].last_live > maxi)
		{
			aref = i;
			maxi = arena->players[i].last_live;
		}
		i++;
	}
	audio_winner(arena->players[aref].header.prog_name, arena);
	mvwprintw(scn->sidebar, 30, 10, "Contestants %zu, \"%s\"\n",
		arena->players[aref].id,
		arena->players[aref].header.prog_name);
	mvwprintw(scn->sidebar, 31, 10, "\"%s\"",
		arena->players[aref].header.comment);
	mvwprintw(scn->sidebar, 32, 20, "WON !\n", arena->players[aref].id);
	wrefresh(scn->sidebar);
	getch();
}
