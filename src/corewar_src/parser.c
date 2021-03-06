/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:42:34 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 18:58:08 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <unistd.h>
#include <fcntl.h>
#include <commons.h>

/*
** @desc convenient wrapper
**       for output debug an exit
** @return boolean
*/

static int		xperror(const char *file,
							const char *message,
							int fd)
{
	ft_fprintf(2, "Error: File \"%s\" %s\n", file, message);
	if (fd >= 0)
		close(fd);
	exit(EXIT_FAILURE);
}

/*
** @desc parse content or return null
**       if the body size is incorect
** @return Maybe[Char*] | Nothing[Null]
*/

static int		parse_content(int fd,
						unsigned char *buffer,
						unsigned int *prog_size)
{
	char			c;

	swap_endian(prog_size, sizeof(unsigned int));
	if ((read(fd, buffer, *prog_size) != *prog_size))
		return (0);
	if ((read(fd, &c, 1)) != 0)
		return (0);
	if (*prog_size > CHAMP_MAX_SIZE)
		return (0);
	return (1);
}

/*
** @desc parse players informations
**       in adhoc structure reference
** @return boolean/succes
*/

int				parseplayers(t_arena *arena,
						char *argv[],
						size_t i,
						struct s_option *opts)
{
	int				fd;
	size_t			ret;

	arena->np = 0;
	while (argv[i] != NULL)
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
			return (xperror(argv[i], "is an invalid file", fd));
		ret = read(fd, &arena->players[i].header, sizeof(t_header));
		if (ret != sizeof(t_header)
			|| !parse_content(fd, arena->players[i].exec,
					&arena->players[i].header.prog_size))
			return (xperror(argv[i], "have an invalid file size.", fd));
		arena->players[i].id = opts->ids[i];
		arena->players[i].last_live = 0;
		arena->players[i].live_cpt = 0;
		close(fd);
		i++;
		arena->np++;
	}
	return (1);
}
