#ifndef READER_H
#define READER_H

struct target {
	char     *host;
	uint16_t port;
	char     *ressource;
};

#define ASSERT_OR_DIE(x) if ((x)) return (NULL)

#endif	/* READER_H */
