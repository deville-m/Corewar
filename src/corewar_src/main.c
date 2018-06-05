/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:02:42 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/05 11:11:34 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <op.h>
#include <ncurses.h>
#include <ft_getopt.h>

int			main(int argc, char *argv[])
{
	struct s_option opts;
	t_arena			arena;

	if (argc < 2 || !parse_options(argc, argv, &opts)
		|| valid_warriors(g_optind, argv) == 0
		|| MEM_SIZE == 0)
		usage();
	if ((argc - g_optind) > MAX_PLAYERS
		|| (argc - g_optind) < 1
		|| !parseplayers(&arena, &argv[g_optind], 0, &opts))
		usage();
	arena.opts = &opts;
	if (opts.audio == 1)
		play_voice("Welcome to Corewar&");
	if (opts.gfx == 1)
	{
		if (!(kernel_gfx(&opts, &arena)))
			return (EXIT_FAILURE);
	}
	else if (!(kernel(&opts, &arena)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
