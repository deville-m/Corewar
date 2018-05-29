/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 10:56:01 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/29 11:10:54 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static struct in_addr	*hostname_to_ip(char *hostname)
{
	struct hostent		*he;
	struct in_addr		**addr_list;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		perror("Could not find host");
		exit(42);
	}
	addr_list = (struct in_addr **)he->h_addr_list;
	if (addr_list && addr_list[0])
		return (addr_list[0]);
	else
		return (NULL);
}

/*
** @desc determine is the current path is an url
** @pattern <host>:<port>/resource
** @return boolean/succes
*/

t_bool					is_url(const char *input)
{
	(void)input;
	return (FALSE);
}

int						open_remote(const char *url)
{
	int					sockfd;
	struct sockaddr_in	cyka;
	struct in_addr		*tmp;

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket client");
		return (42);
	}
	cyka.sin_family = AF_INET;
	cyka.sin_port = htons(4242);
	if (!(tmp = hostname_to_ip((char*)url)))
	{
		perror("Could not resolve hostname");
		return (42);
	}
	cyka.sin_addr = *tmp;
	if (connect(sockfd, (struct sockaddr *)&cyka, sizeof(cyka)) < 0)
	{
		perror("connect client");
		return (42);
	}
	return (sockfd);
}
