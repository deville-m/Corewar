/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:14:39 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/22 13:48:22 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <ft_getopt.h>
#include <libft.h>

/*
** @desc Simple getopt wrapper
** @return boolean
*/

t_bool	parse_options(int argc, char *argv[],
				struct s_option *opts)
{
	int	c;

	opts->gfx = FALSE;
	opts->dump = 0;
	while ((c = ft_getopt(argc, argv, "hxd:n:")) != -1)
	{
		if (c == 'd')
			opts->dump = ft_atoi(g_optarg);
		else if (c == 'x')
			opts->gfx = TRUE;
		else if (c == 'n')
			opts->cycles = ft_atoi(g_optarg);
		else if (c == 'h')
			usage();
	}
	return (TRUE);
}
