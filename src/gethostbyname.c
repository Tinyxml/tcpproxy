/*
 * gethostbyname.c
 *
 * Author: lvbingc <lvbingc@gmail.com>
 *
 */

#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

#define bool int
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
	int opt;
	char *host_c, **pptr,;
	bool showversion = FALSE;
	bool havehostarg = FALSE;
	bool havelocalarg = FALSE;
	bool haveportarg = FALSE;
	char str[100];
	struct hostent *host_s;

	/*
	 * v For version
	 * l For localhost port
	 * h For remote ip
	 * p For remote port
	 */

	while ((opt = getopt(argc, argv, "vl:h:p:")) != -1) {
		switch (opt) {
		case 'v':
			showversion = TRUE;
			break;
		case 'h':
			havehostarg = TRUE;
			host_c = optarg;
			break;
		case 'l':
			havelocalarg = TRUE;
			break;
		case 'p':
			haveportarg = TRUE;
			break;
		default:
			break;
		}
	}

	if (showversion) {
		printf("gethostbyname Version 1.1\n");
	}

	if (havehostarg) {
		if ((host_s = gethostbyname(host_c)) == NULL ) {
			printf("gethostbyname error %d--%s\n", errno, strerror(errno));
		}
	}

	printf("%s\n", host_s->h_name);
	switch (host_s->h_addrtype) {
	case AF_INET:
	case AF_INET6:
		for (pptr = host_s->h_addr_list; *pptr != NULL ; pptr++) {
			inet_pton(host_s->h_addrtype, *pptr, str, sizeof(str));
			printf("%s\n", str);
		}
		break;
	default:
		printf("unkown proto");
	}

	for (pptr = host_s->h_aliases; *pptr != NULL ; pptr++) {
		printf("%s\n", *pptr);
	}

	return 0;
}
