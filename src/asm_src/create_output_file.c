/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_output_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:34:58 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/10 18:41:02 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

/*
** create_output_file:
**     takes input filename from env and create filename.cor file with it.
**     returns the file descriptor of filename.cor
*/

int		create_output_file(t_env *env)
{
	char	*new;
	int		fd;

	new = ft_strrchr(env->input_name, '.');
	*(new) = '\0';
	new = ft_strjoin(env->input_name, ".cor");
	if (!new)
		bug_err("Error while malloc new file name\n");
	if ((fd = open(new, O_CREAT | O_EXLOCK | O_TRUNC | O_WRONLY)) == -1)
		bug_err("Error while create new file\n");
	free(new);
	return (fd);
}
