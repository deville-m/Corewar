/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:14:39 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/28 15:33:44 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <ft_getopt.h>
#include <libft.h>

static void		init_ids(int *foo,
					int i, int j)
{
	while (j < MAX_PLAYERS)
	{
		foo[j] = i;
		i--;
		j++;
	}
}

/*
** @desc Simple getopt wrapper
** @return boolean
*/

t_bool			parse_options(int argc, char *argv[],
					struct s_option *opts)
{
	int			c;
	int 		i;

	opts->gfx = FALSE;
	opts->trash = FALSE;
	opts->ids_activated = FALSE;
	opts->dump = 0;
	i = 0;
	init_ids(opts->ids, -1, 0);
	while ((c = ft_getopt(argc, argv, "hxtd:n:")) != -1)
	{
		if (c == 'd')
			opts->dump = ft_atoi(g_optarg);
		else if (c == 'x')
			opts->gfx = TRUE;
		else if (c == 't')
			opts->trash = TRUE;
		else if (c == 'n')
		{
			/* if (i > MAX_PLAYERS) */
			/* 	usage(); */
			/* opts->ids_activated = TRUE; */
			/* opts->ids[i] = ft_atoi(g_optarg); */
			/* i++; */
		}
		else if (c == 'h')
			usage();
	}
	return (TRUE);
}
