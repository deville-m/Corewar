/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:14:39 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 19:20:13 by ctrouill         ###   ########.fr       */
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
		i++;
		j++;
	}
}

static void		init_defaults(struct s_option *opts)
{
	opts->gfx = FALSE;
	opts->verbose = 1;
	opts->ids_activated = FALSE;
	opts->dump = -1;
	opts->audio = FALSE;
	init_ids(opts->ids, 666, 0);
}

static void		apply_n(int *i, struct s_option *opts)
{
	if (*i > MAX_PLAYERS)
		usage();
	opts->ids_activated = TRUE;
	opts->ids[*i] = ft_atoi(g_optarg);
	(*i)++;
}

/*
** @desc Simple getopt wrapper
** @return boolean
*/

t_bool			parse_options(int argc, char *argv[],
					struct s_option *opts)
{
	int			c;
	int			i;

	i = 0;
	init_defaults(opts);
	while ((c = ft_getopt(argc, argv, "ahxtd:n:v:")) != -1)
	{
		if (c == 'd')
			opts->dump = ft_atoi(g_optarg);
		else if (c == 'a')
			opts->audio = TRUE;
		else if (c == 'x')
			opts->gfx = TRUE;
		else if (c == 'v')
			opts->verbose = ft_atoi(g_optarg);
		else if (c == 'n')
			apply_n(&i, opts);
		else if (c == 'h')
			usage();
	}
	return (TRUE);
}
