/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:44:30 by tauer             #+#    #+#             */
/*   Updated: 2024/12/16 09:04:41 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Server.hpp"
#include <algorithm>

bool Server::_Signal = false; // init static variable

Server::Server(char **argv) : _Port(atoi(argv[1])), _SocketFd(-1), _pass(false), clients(), channels()
{
	//! si il y a un argv 2 il y a un password
	if (argv[2]) {
		_pass = true;
		_password = argv[2];
	}
}

