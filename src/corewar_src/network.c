/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 10:56:01 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 13:39:22 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*
** @desc determine is the current path is an url
** @pattern <host>:<port>/resource
** @return boolean/succes
*/

t_bool					is_url(const char *input)
{
	if (input[0] == 'c'
		&& input[1] == 'o'
		&& input[2] == 'r'
		&& input[3] == ':'
		&& input[4] == '/'
		&& input[5] == '/')
		return (TRUE);
	return (FALSE);
}

/* static void				clea(char **split, */
/* 							size_t i) */
/* { */
/* 	if (split != NULL) */
/* 	{ */
/* 		while (split[i] != NULL) */
/* 			free(split[i]); */
/* 		free(split); */
/* 	} */
/* } */

int						open_remote(const char *url)
{
	int					sockfd;
	struct sockaddr_in	cyka;
	char				**iname;

	iname = ft_strsplit(url, ':');
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("[!!] Error while opening socket");
		exit(1);
	}
	cyka.sin_family = AF_INET;
	cyka.sin_addr.s_addr = inet_addr(&iname[1][2]);
	cyka.sin_port = htons(COR_PORT);
	if (connect(sockfd, (struct sockaddr *)&cyka, sizeof(cyka)) == -1)
	{
		perror("[!!] Error while connecting socket");
		exit(1);
	}
	ft_printf("Connected to %s, port %d\n", &iname[1][2], COR_PORT);
	if (!check_magic(sockfd))
	{
		ft_printf("Remote file \"%s\" have an invalid magic number\n", url);
		exit(1);
	}
	return (sockfd);
}
