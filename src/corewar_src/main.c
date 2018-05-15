/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:02:42 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/15 08:45:14 by ctrouill         ###   ########.fr       */
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

	opts.dump = 0;
	if (argc < 2 || !parse_options(argc, argv, &opts)
		|| valid_warriors(g_optind, argv) == FALSE)
		usage();
	if ((argc - g_optind) > MAX_PLAYERS
		|| (argc - g_optind) < 1
		|| !parseplayers(&arena, &argv[optind], 0))
		usage();
	if (!(kernel(&opts, &arena)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
