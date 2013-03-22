/*
 * tcpproxy.c
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

int remote_port, local_port;
int listen_fd;
char *remote_host;
struct sockaddr_in server_addr;

int create_server(int local_port);
int main(int argc, char *argv[]) {
	int opt;
	char **pptr;
	bool show_version_flag = FALSE;
	bool remote_host_flag = FALSE;
	bool local_port_flag = FALSE;
	bool remote_port_flag = FALSE;
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
			show_version_flag = TRUE;
			break;
		case 'h':
			remote_host_flag = TRUE;
			remote_host = optarg;
			break;
		case 'l':
			local_port_flag = TRUE;
			local_port = atoi(optarg);
			break;
		case 'p':
			remote_port_flag = TRUE;
			remote_port = atoi(optarg);
			break;
		default:
			break;
		}
	}

	if (show_version_flag) {
		printf("TcpProxy Version 1.1\n");
	}

	if (!(local_port_flag && remote_port_flag && remote_port_flag)) {
		printf("Usage: tcpproxy -l 8080 -h 127.0.0.1 -p 80\n");
	} else {
		printf("tcpproxy -l %d -h %s -p %d\n", local_port, remote_host,
				remote_port);
	}

	create_server(local_port);
	create_client(remote_host, remote_port);

//
//	if (remote_host_flag) {
//		if ((host_s = gethostbyname(remote_host)) == NULL ) {
//			printf("gethostbyname error %d--%s\n", errno, strerror(errno));
//		}
//	}
//
//	printf("%s\n", host_s->h_name);
//	switch (host_s->h_addrtype) {
//	case AF_INET:
//	case AF_INET6:
//		for (pptr = host_s->h_addr_list; *pptr != NULL ; pptr++) {
//			inet_pton(host_s->h_addrtype, *pptr, str, sizeof(str));
//			printf("%s\n", str);
//		}
//		break;
//	default:
//		printf("unkown proto");
//	}
//
//	for (pptr = host_s->h_aliases; *pptr != NULL ; pptr++) {
//		printf("%s\n", *pptr);
//	}

	return 0;
}

int create_server(int local_port) {
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd = -1) {
		printf("socket() error %d : %s", errno, strerror(errno));
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(local_port);
	server_addr.sin_addr.s_addr=htonl(ANYADDR);
}

