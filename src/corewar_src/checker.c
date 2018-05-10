/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:42:25 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/10 15:39:31 by ctrouill         ###   ########.fr       */
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

static t_bool	xperror(const char *message)
{
	ft_fprintf(2, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}

/*
** @desc verify magic
**       number of warrior
** @return boolean
*/

static t_bool	check_magic(int fd)
{
	t_header	header;

	if (!(read(fd, &header, sizeof(header))))
		return (FALSE);
	swap_endian(&header.magic, sizeof(header.magic));
	swap_endian(&header.prog_size, sizeof(header.prog_size));
	return (header.magic == COREWAR_EXEC_MAGIC);
}

/*
** @desc check if the warrior cursor
**       is valid
** @return boolean
*/

static t_bool	is_valid_warrior(const char *filename)
{
	int			fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (xperror("File doesn't exists"));
	if (!(check_magic(fd)))
		return (xperror("Invalid magic number"));
	close(fd);
	return (TRUE);
}

/*
** @desc Check warrior validity
**       before vm processing
** @return boolean
*/

t_bool			valid_warriors(uint32_t i,
						char *argv[])
{
	while (argv[i] != NULL)
	{
		if (is_valid_warrior(argv[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
