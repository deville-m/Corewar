/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:02:42 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/10 09:22:37 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <op.h>
#include <ncurses.h>
#include <ft_getopt.h>

int			main(int argc, char *argv[])
{
	struct s_option opts;

	opts.dump = 0;
	if (argc < 2 || !parse_options(argc, argv, &opts))
		usage();
	if ((argc - g_optind) > MAX_PLAYERS
		|| (argc - g_optind) < 1)
		usage();
	printf("Option: %zu %zu | %d - %d\n", opts.dump, opts.cycles, g_optind , argc);
	if (!(kernel(&opts)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
