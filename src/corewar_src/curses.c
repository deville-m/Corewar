/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:05:09 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/10 12:39:19 by ctrouill         ###   ########.fr       */
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
	curs_set(0);
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	keypad(stdscr, TRUE);
	atexit((void*)endwin);
}

void		alloc_window(WINDOW *arena, WINDOW *status)
{
	arena = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	status = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));
}

void		apply_windows(WINDOW *arena, WINDOW *status)
{
	clear();
	arena = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	status = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));
	wbkgd(arena, COLOR_PAIR(1));
	wbkgd(status, COLOR_PAIR(1));
	box(arena, ACS_VLINE, ACS_HLINE);
	box(status, ACS_VLINE, ACS_HLINE);
}
