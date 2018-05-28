/*
 * Simple proof-of-concept
 * that read file poited by url
 * passed in argv, and print
 * his content to `stdout`
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "reader.h"

static struct request*
parseurl(const char *url,
		 uint16_t i)
{
	struct request *req = NULL;

	if ((req = (struct request*)malloc(sizeof(struct request))) == NULL) {
		perror("malloc()");
	}
	return (req);
}

int
main(int argc, char *argv[])
{
	struct request *t = NULL;

	if (argc != 2) {
		dprintf(2, "Argument needed\n");
		exit(EXIT_FAILURE);
	}
	if ((t = parseurl(argv[1], 0)) == NULL) {
		dprintf(2, "Invalid url\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
