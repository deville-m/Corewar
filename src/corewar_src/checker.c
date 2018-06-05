/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:42:25 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 18:11:47 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <fcntl.h>
#include <commons.h>

/*
** @desc convenient wrapper
**       for output debug an exit
** @return boolean
*/

static int	xperror(const char *f, const char *message)
{
	ft_fprintf(2, "Error: File \"%s\" %s\n", f, message);
	exit(EXIT_FAILURE);
}

/*
** @desc verify magic
**       number of warrior
** @return boolean
*/

int			check_magic(int fd)
{
	t_header	header;

	if (!(read(fd, &header, sizeof(header))))
		return (0);
	swap_endian(&header.magic, sizeof(header.magic));
	swap_endian(&header.prog_size, sizeof(header.prog_size));
	return (header.magic == COREWAR_EXEC_MAGIC);
}

/*
** @desc check if the warrior cursor
**       is valid
** @return boolean
*/

static int	is_valid_warrior(const char *filename)
{
	int			fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (xperror(filename, " doesn't exists"));
	if (!(check_magic(fd)))
		return (xperror(filename, "have an invalid magic number"));
	close(fd);
	return (1);
}

/*
** @desc Check warrior validity
**       before vm processing
** @return boolean
*/

int			valid_warriors(uint32_t i,
						char *argv[])
{
	while (argv[i] != NULL)
	{
		if (is_valid_warrior(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
