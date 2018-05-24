/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:05:09 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/24 15:04:54 by ctrouill         ###   ########.fr       */
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
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	timeout(0);
	atexit((void*)endwin);
}

void print_status(t_scene *scene, int cycle,
			int processes, t_arena *arena)
{
	int x;
	int y;
	int z;
	int k;

	z = 0;
	k = 0;
	getmaxyx(scene->sidebar, y, x);
	wattron(scene->sidebar, A_BOLD);
	mvwprintw(scene->sidebar, y/6 + 2, x/5, "Cycles: %d", cycle);
	mvwprintw(scene->sidebar, y/6 + 4, x/5, "Processes: %d", processes);
	mvwprintw(scene->sidebar, y/6 + 6, x/5, "-----------------");
	mvwprintw(scene->sidebar, y/6 + 8, x/5, "CYCLE_TO_DIE: %d", CYCLE_TO_DIE);
	mvwprintw(scene->sidebar, y/6 + 10, x/5, "CYCLE_DELTA: %d", CYCLE_DELTA);
	mvwprintw(scene->sidebar, y/6 + 12, x/5, "NBR_LIVE: %d", NBR_LIVE);
	mvwprintw(scene->sidebar, y/6 + 14, x/5, "MAX_CHECKS: %d", MAX_CHECKS);
	mvwprintw(scene->sidebar, y/6 + 16, x/5, "-----------------");
	while (z < arena->np)
	{
		mvwprintw(scene->sidebar, y/6 + 17 + k, x/5,
			"Player %d: %s", z, arena->players[z].header.prog_name);
		mvwprintw(scene->sidebar, y/6 + 17 + k + 1, x/5,
			"  \\_ [ Last Live ] -> %u", arena->players[z].last_live);
		k += 2;
		z++;
	}
	wattroff(scene->sidebar, A_BOLD);
	wrefresh(scene->sidebar);
}

static void	set_delimiters(t_scene *scene, t_arena *arena)
{
	int x;
	int y;

	getmaxyx(scene->sidebar, y, x);
	wattron(scene->sidebar, A_BOLD | COLOR_PAIR(1));
	mvwprintw(scene->sidebar, 2, x/5, "   ______                                  ");
	mvwprintw(scene->sidebar, 3, x/5, "  / ____/___  ________ _      ______ ______");
	mvwprintw(scene->sidebar, 4, x/5, " / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/");
	mvwprintw(scene->sidebar, 5, x/5, "/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    ");
	mvwprintw(scene->sidebar, 6, x/5, "\\____/\\____/_/   \\___/|__/|__/\\__,_/_/");
	mvwprintw(scene->sidebar, 9, x/5, "      By: mdeville, rbaraud & ctrouill   ");
	wattroff(scene->sidebar, A_BOLD | COLOR_PAIR(1));
	mvwhline(scene->sidebar, y / 6, 1, ACS_HLINE, x - 2);
	print_status(scene, 0, 0, arena);
}

void	alloc_window(t_scene *scene, t_arena *arena)
{
	scene->memory = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	scene->sidebar = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));

	scene->memory = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	scene->sidebar = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));;
	box(scene->memory, ACS_VLINE, ACS_HLINE);
	box(scene->sidebar, ACS_VLINE, ACS_HLINE);
	set_delimiters(scene, arena);
}

void		apply_windows(t_scene *scene, t_arena *arena)
{
	clear();
	scene->memory = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	scene->sidebar = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));;
	box(scene->memory, ACS_VLINE, ACS_HLINE);
	box(scene->sidebar, ACS_VLINE, ACS_HLINE);
	set_delimiters(scene, arena);
}
