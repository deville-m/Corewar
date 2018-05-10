/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:05:09 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/10 12:03:25 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <curses.h>

/*
** @desc Initialise curses librarie
**       and set cleanup callback when
**       exiting.
** @return nil
*/

void		init_curses(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	atexit((void*)endwin);
}

void		windows_borders(WINDOW *arena, WINDOW *status)
{
	clear();
	arena = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	status = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));
	box(arena, ACS_VLINE, ACS_HLINE);
	box(status, ACS_VLINE, ACS_HLINE);
	/* TODO: Controler le render de l'arena/status */
	wrefresh(arena);
	wrefresh(status);
	getch();
}
