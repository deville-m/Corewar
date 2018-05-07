/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:16:53 by rbaraud           #+#    #+#             */
/*   Updated: 2018/05/07 18:14:25 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

int	craft_directs(t_env *env, int fd)
{
	char	buf;
	int		ret;
	int		offset;

	if (!env)
		return (0);

	if ((ret = read(fd, &buf, 1)) < 1)
		return (0);
	offset = ret;
	if (buf == LABEL_CHAR)
	{
		while ((ret = read(fd, &buf, 1)) != 0)
		{
			if (ret == -1)
				return (0);
			offset += ret;
			if (ret == 0 || !ft_strchr(LABEL_CHARS, buf))
			{
				ft_printf("direct label offset = %d\n", offset);
				return (1);
			}

		}
	}
	else if (ft_strchr(BASE, buf))
	{
		while ((ret = read(fd, &buf, 1)) != 0)
		{
			if (ret == -1)
				return (0);
			offset += ret;
			if (ret == 0 || !ft_strchr(BASE, buf))
			{
				ft_printf("direct offset = %d\n", offset);
				return (1);
			}
		}
	}
	return (0);
}

int	oh_a_comment_pass_it(int fd)
{
	int		ret;
	char	buf;

	ft_printf("passing a comment\n");

	while ((ret = read(fd, &buf, 1)) != 0)
	{
		if (ret == -1)
			bug_err("Error while passing comment");
		if (buf == EOL)
		{
			if (lseek(fd, -1, SEEK_CUR) == -1)
				bug_err("Error while passing comment");
			return (1);
		}
	}
	return (0); // est-ce qu'un commentaire avant la fin du fichier sans EOL est une erreur ? Ici oui mais pas forcement sur le vrai...
}
