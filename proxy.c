#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void	server(int fd)
{
	struct addrinfo main, *reserve;
	int sockfd;
	char buf[1024];
	int byte_count;
	char *header;

	header = strdup("GET /index.html HTTP/1.1\r\nHost: www.qst0.com\r\n\r\n");
	memset(&main, 0,sizeof(main));
	main.ai_family=AF_UNSPEC;
	main.ai_socktype = SOCK_STREAM;
	getaddrinfo("www.qst0.com","80", &main, &reserve);
	sockfd = socket(reserve->ai_family,reserve->ai_socktype,reserve->ai_protocol);
	connect(sockfd,reserve->ai_addr,reserve->ai_addrlen);
	send(sockfd,header,strlen(header),0);
	byte_count = recv(sockfd,buf, sizeof(buf) - 1,0);
	buf[byte_count] = 0;
	write(fd, buf, strlen(buf));
	printf("%s",buf);
}

int		main(void)
{
	char				str[100];
	int					listen_fd;
	int					comm_fd;
	struct sockaddr_in	servaddr;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(22000);
	bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listen_fd, 10);
	while (1)
	{
		comm_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
		read(comm_fd, str, 100);
		server(comm_fd);
	}
}
