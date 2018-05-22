/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:05:09 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/22 22:24:57 by iomonad          ###   ########.fr       */
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
	keypad(stdscr, TRUE);
	if(has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	atexit((void*)endwin);
}

void		alloc_window(WINDOW *arena, WINDOW *status)
{
	arena = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	status = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));
}

static void print_status(WINDOW *status, int cycle, int processes)
{
	int x;
	int y;

	getmaxyx(status, y, x);
	wattron(status, A_BOLD);
	mvwprintw(status, y/6 + 2, x/5, "Cycle: %d", cycle);
	mvwprintw(status, y/6 + 4, x/5, "Processes: %d", cycle);
	mvwprintw(status, y/6 + 6, x/5, "-------");
	mvwprintw(status, y/6 + 8, x/5, "CYCLE_TO_DIE: %d", CYCLE_TO_DIE);
	mvwprintw(status, y/6 + 10, x/5, "CYCLE_DELTA: %d", CYCLE_DELTA);
	mvwprintw(status, y/6 + 12, x/5, "NBR_LIVE: %d", NBR_LIVE);
	mvwprintw(status, y/6 + 14, x/5, "MAX_CHECKS: %d", MAX_CHECKS);
	wattroff(status, A_BOLD);
}

static void	set_delimiters(WINDOW *status)
{
	int x;
	int y;

	getmaxyx(status, y, x);
	wattron(status, A_BOLD | COLOR_PAIR(1));
	mvwprintw(status, 2, x/5, "   ______                                  ");
	mvwprintw(status, 3, x/5, "  / ____/___  ________ _      ______ ______");
	mvwprintw(status, 4, x/5, " / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/");
	mvwprintw(status, 5, x/5, "/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    ");
	mvwprintw(status, 6, x/5, "\\____/\\____/_/   \\___/|__/|__/\\__,_/_/");
	mvwprintw(status, 9, x/5, "      By: mdeville, rbaraud & ctrouill   ");
	wattroff(status, A_BOLD | COLOR_PAIR(1));
	mvwhline(status, y / 6, 1, ACS_HLINE, x - 2);
//	print_status(status, 1337, 1337);
}

void		apply_windows(WINDOW *arena, WINDOW *status)
{
	clear();
	arena = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	status = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));;
	box(arena, ACS_VLINE, ACS_HLINE);
	box(status, ACS_VLINE, ACS_HLINE);
	set_delimiters(status);
}
