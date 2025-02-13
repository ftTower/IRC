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

void Server::Init()
{
	struct sockaddr_in add;
	struct pollfd NewPoll;
	int en;

	add.sin_family = AF_INET;
	add.sin_port = htons(this->Port());
	add.sin_addr.s_addr = INADDR_ANY;
	_SocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFd() == -1)
		throwSocketOptionError(-1, ERR_SOCKET);
	en = 1;
	if (setsockopt(SocketFd(), SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throwSocketOptionError(-1, ERR_SOCKET_OPTION_R);
	if (fcntl(SocketFd(), F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error(ERR_SOCKET_OPTION_N));
	if (bind(SocketFd(), (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error(ERR_SOCKET_BIND));
	if (listen(SocketFd(), SOMAXCONN) == -1)
		throw(std::runtime_error(ERR_SOCKET_LISTEN));
	NewPoll.fd = SocketFd();
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);
}

void Server::Run()
{
	Init();
	initMessage();

	//! tant que le server est allume on accepte de la data ou des nouveaux clients
	while (!Server::_Signal)
	{
		if ((poll(&fds[0], fds.size(), 100) == -1) && Server::_Signal == false)
			throw(std::runtime_error(ERR_POLL_FAIL));
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == SocketFd())
					AcceptNewClient();
				else
					ReceiveNewData(fds[i].fd);
			}
		}
		//! affiche le message toute les x secondes
		if (shouldTriggerEveryXSeconds(1))
			serverMessage();
		
	}
	CloseFds();
}

// recupere une commande ou kick le client
void Server::ReceiveNewData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);

	if (bytes <= 0)
		kickClient(fd);
	else
	{
		buff[bytes] = '\0';
		handleCmds(*this, fd, buff);
	}
}
