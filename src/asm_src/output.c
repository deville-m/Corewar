/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 19:02:52 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/07 20:06:52 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

int		create_file(t_env *env)
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

/*
void	craft_prog(t_env *env, int fd)
{
	if (!env)
		return ;
	write(fd, "toto", 4);
}
*/
int		craft_file(t_env *env)
{
	int	fd;

	fd = create_file(env);
	write(fd, env->header, sizeof(t_header));
//	craft_prog(env, fd);
	return (1);
}
