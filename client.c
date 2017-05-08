/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 21:22:11 by rpassafa          #+#    #+#             */
/*   Updated: 2017/05/07 21:22:12 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int					sockfd;
	char				recvline[1024];
	struct sockaddr_in	servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(22000);
	inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	write(sockfd, "ping", 5);
	read(sockfd, recvline, 1024);
	printf("%s", recvline);
}
