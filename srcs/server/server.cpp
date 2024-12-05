/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:44:30 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 01:56:22 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/server.hpp"

bool Server::_Signal = false; // init static variable

Server::Server(int Port) : _Port(Port), _SocketFd(-1)
{
}

//! methods

void Server::Init()
{
	struct sockaddr_in add;
	struct pollfd NewPoll;

	add.sin_family = AF_INET;
	add.sin_port = htons(this->Port());
	add.sin_addr.s_addr = INADDR_ANY;

	_SocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFd() == -1)
		throwSocketOptionError(-1, ERR_SOCKET);

	int en = 1;
	if (setsockopt(SocketFd(), SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throwSocketOptionError(-1, ERR_SOCKET_OPTION_R);
	if (fcntl(SocketFd(), F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error(ERR_SOCKET_OPTION_N));
	if (bind(SocketFd(), (struct sockaddr *)&add, sizeof(add)) == -1)
		throw (std::runtime_error(ERR_SOCKET_BIND));
	if (listen(SocketFd(), SOMAXCONN) == -1)
		throw (std::runtime_error(ERR_SOCKET_LISTEN));
		
	NewPoll.fd = SocketFd();
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;

	fds.push_back(NewPoll);
}

void Server::Run()
{
	Init();
	std::cout << GREEN_BG << BOLD_WHITE << "SERVER ON" << RESET << std::endl << BOLD_BLUE << "\tPort : " << RESET << YELLOW_TEXT << this->Port() << RESET << std::endl;
	while (!Server::_Signal)
	{
	}
}

//! getters

int Server::Port() const
{
	return (_Port);
}

int Server::SocketFd() const
{
	return (_SocketFd);
}

//! signal

void Server::SignalHandler(int signum)
{
	(void)signum;
	//! print for signal
	Server::_Signal = true;
}

//?cleaning

void Server::CloseFds()
{
	for (size_t i = 0; i < fds.size(); i++)
	{
		//! print for logout
		if (clients[i].Fd() >= 0)
			close(clients[i].Fd());
	}
}

void Server::ClearClients(int fd)
{
	for (size_t i = 0; i < fds.size(); i++)
		if (fds[i].fd == fd)
			fds.erase(fds.begin() + i);
	for (size_t i = 0; i < clients.size(); i++)
		if (clients[i].Fd() == fd)
		{
			clients.erase(clients.begin() + i);
			break ;
		}
}
