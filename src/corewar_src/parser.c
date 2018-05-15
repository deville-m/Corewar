/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:42:34 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/15 09:14:38 by ctrouill         ###   ########.fr       */
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

static t_bool			xperror(const char *file,
								const char *message)
{
	ft_fprintf(2, "Error: File \"%s\" %s\n", file, message);
	exit(EXIT_FAILURE);
}

/*
** @desc parse content or return null
**       if the body size is incorect
** @return Maybe[Char*] | Nothing[Null]
*/

static unsigned char	*parse_content(int fd, uint32_t size)
{
	unsigned char		*buffer;
	char		nil[0x2];

	buffer = (unsigned char*)ft_strnew(CHAMP_MAX_SIZE);
	swap_endian(&size, sizeof(size));
	if ((read(fd, buffer, size) != size))
		return (NULL);
	if ((read(fd, nil, 0x13)) != 0)
		return (NULL);
	return (buffer);
}

/*
** @desc parse players informations
**       in adhoc structure reference
** @return boolean/succes
*/

t_bool					parseplayers(t_arena *arena,
									 char *argv[],
									 size_t i)
{
	int					fd;
	unsigned int		id;
	unsigned short		np;

	id = -1;
	np = 0;
	while (argv[i] != NULL)
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
			return (xperror(argv[i] ,"is an invalid file"));
		ft_printf("Processing: %s with fd %d\n", argv[i], fd);
		if (read(fd, &arena->players[i].header, sizeof(t_header)) < 0
			|| ((arena->players[i].exec = parse_content(fd,
					arena->players[i].header.prog_size))== NULL))
			return (xperror(argv[i], "have an invalid file size."));
		arena->players[i].id = id--;
		arena->players[i].last_live = 0;
		arena->players[i].live_cpt = 0;
		close(fd);
		i++;
		np++;
	}
	return ((arena->np = np) | 1);
}
