/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:05:09 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/01 13:56:49 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <curses.h>

static void			deploy_informations(t_scene *s, int cycle,
							int processes, t_arena *arena)
{
	int				x;
	int				y;

	getmaxyx(s->sidebar, y, x);
	wattron(s->sidebar, A_BOLD);
	mvwprintw(s->sidebar, y / 6 + 2, x / 5, "Cycles: %d", cycle);
	mvwprintw(s->sidebar, y / 6 + 4, x / 5, "Processes: %-6d", processes);
	mvwprintw(s->sidebar, y / 6 + 6, x / 5, "-----------------");
	mvwprintw(s->sidebar, y / 6 + 8, x / 5, "CYCLE_TO_DIE: %-6d",
						arena->cycle_to_die);
	mvwprintw(s->sidebar, y / 6 + 10, x / 5, "CYCLE_DELTA: %d", CYCLE_DELTA);
	mvwprintw(s->sidebar, y / 6 + 12, x / 5, "NBR_LIVE: %d", NBR_LIVE);
	mvwprintw(s->sidebar, y / 6 + 14, x / 5, "MAX_CHECKS: %d", MAX_CHECKS);
	mvwprintw(s->sidebar, y / 6 + 16, x / 5, "-----------------");
}

/*
** @desc Deploy side bar library
**       and print status informations.
** @return nil
*/

void				print_status(t_scene *s, int cycle,
						int processes, t_arena *arena)
{
	int x;
	int y;
	int z;
	int k;

	z = 0;
	k = 0;
	getmaxyx(s->sidebar, y, x);
	deploy_informations(s, cycle, processes, arena);
	while (z < arena->np)
	{
		mvwprintw(s->sidebar, y / 6 + 18 + k, x / 5,
			"Player %d: %.37s", arena->opts->ids[z],
				arena->players[z].header.prog_name);
		mvwprintw(s->sidebar, y / 6 + 18 + k + 1, x / 5,
			"  \\_ [ Last Live ] -> %u", arena->players[z].last_live);
		mvwprintw(s->sidebar, y / 6 + 18 + k + 2, x / 5,
			"  \\_ [ Lives / CYCLE_TO_DIE ] -> %u", arena->players[z].live_cpt);
		k += 4;
		z++;
	}
	wattroff(s->sidebar, A_BOLD);
	wrefresh(s->sidebar);
}

static void			set_delimiters(t_scene *s, t_arena *arena)
{
	int				x;
	int				y;

	getmaxyx(s->sidebar, y, x);
	wattron(s->sidebar, A_BOLD | COLOR_PAIR(1));
	mvwprintw(s->sidebar, 2, x / 5,
		"   ______                                  ");
	mvwprintw(s->sidebar, 3, x / 5,
		"  / ____/___  ________ _      ______ ______");
	mvwprintw(s->sidebar, 4, x / 5,
		" / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/");
	mvwprintw(s->sidebar, 5, x / 5,
		"/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    ");
	mvwprintw(s->sidebar, 6, x / 5,
		"\\____/\\____/_/   \\___/|__/|__/\\__,_/_/");
	mvwprintw(s->sidebar, 9, x / 5,
		"By: mdeville, rbaraud, ctrouill & dchiche  ");
	wattroff(s->sidebar, A_BOLD | COLOR_PAIR(1));
	mvwhline(s->sidebar, y / 6, 1, ACS_HLINE, x - 2);
	print_status(s, 0, 0, arena);
}

void				alloc_window(t_scene *scene, t_arena *arena)
{
	scene->memory = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	scene->sidebar = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));
	scene->memory = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	scene->sidebar = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));
	box(scene->memory, ACS_VLINE, ACS_HLINE);
	box(scene->sidebar, ACS_VLINE, ACS_HLINE);
	scene->speed = MIN_SPEED;
	scene->pause = TRUE;
	set_delimiters(scene, arena);
}

void				apply_windows(t_scene *scene, t_arena *arena)
{
	clear();
	scene->memory = subwin(stdscr, LINES, (COLS - COLS / 4), 0, 0);
	scene->sidebar = subwin(stdscr, LINES, (COLS / 4), 0, (COLS - COLS / 4));
	box(scene->memory, ACS_VLINE, ACS_HLINE);
	box(scene->sidebar, ACS_VLINE, ACS_HLINE);
	set_delimiters(scene, arena);
}
