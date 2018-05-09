/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:02:42 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/09 14:43:04 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <ncurses.h>

int		main(int argc, char *argv[])
{
	if (argc == 2) {
		initscr();
		printw("%s", argv[1]);
		refresh();
		getch();
		endwin();
	}
	return (EXIT_SUCCESS);
}
