/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:42:34 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/13 17:52:56 by ctrouill         ###   ########.fr       */
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

static t_bool			xperror(const char *message)
{
	ft_fprintf(2, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}

/*
** @desc parse content or return null
**       if the body size is incorect
** @return Maybe[Char*] | Nothing[Null]
*/

static unsigned char	*parse_content(int fd, int offset)
{
	unsigned char		*buffer;

	if (!(read(fd, &buffer, CHAMP_MAX_SIZE) == CHAMP_MAX_SIZE))
		return (NULL);
	if ((read(fd, NULL, 0x13)) != 0)
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
	int fd;

	while (argv[i] != NULL)
	{
		printf("Processing: %s\n", argv[i]);
		if ((fd = open(argv[i], O_RDONLY) < 0))
			return (xperror("Invalid file"));
		if (read(fd, &arena->players[i].header, sizeof(t_header)) < 0
			|| ((arena->players[i].exec = parse_content(fd, 0)) == NULL))
			return (xperror("Invalid file size."));
		arena->players[i].id = i;
		arena->players[i].last_live = 0;
		arena->players[i].live_cpt = 0;
		arena->players[i].processes = NULL;
		close(fd);
		i++;
	}
	return (TRUE);
}
