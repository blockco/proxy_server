/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proxy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 21:22:13 by rpassafa          #+#    #+#             */
/*   Updated: 2017/05/07 21:27:32 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROXY_H
# define PROXY_H
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef struct		s_sock
{
	struct addrinfo main;
	struct addrinfo *reserve;
	int				sockfd;
	char			buf[1024];
	int				byte_count;
	char			*header;
}					t_sock;
#endif
