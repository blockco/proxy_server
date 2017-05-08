/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 21:22:07 by rpassafa          #+#    #+#             */
/*   Updated: 2017/05/07 21:25:08 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proxy.h"

void	server(int fd)
{
	t_sock main_socket;

	main_socket.header =
	strdup("GET /index.html HTTP/1.1\r\nHost: www.qst0.com\r\n\r\n");
	memset(&main_socket.main, 0, sizeof(main_socket.main));
	main_socket.main.ai_family = AF_UNSPEC;
	main_socket.main.ai_socktype = SOCK_STREAM;
	getaddrinfo("www.qst0.com", "80", &main_socket.main, &main_socket.reserve);
	main_socket.sockfd = socket(main_socket.reserve->ai_family,
	main_socket.reserve->ai_socktype, main_socket.reserve->ai_protocol);
	connect(main_socket.sockfd, main_socket.reserve->ai_addr,
	main_socket.reserve->ai_addrlen);
	send(main_socket.sockfd, main_socket.header, strlen(main_socket.header), 0);
	main_socket.byte_count = recv(main_socket.sockfd,
	main_socket.buf, sizeof(main_socket.buf) - 1, 0);
	main_socket.buf[main_socket.byte_count] = 0;
	write(fd, main_socket.buf, strlen(main_socket.buf));
	printf("%s", main_socket.buf);
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
