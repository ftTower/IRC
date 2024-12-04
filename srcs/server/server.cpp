/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:44:30 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 23:12:37 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/server.hpp"

bool Server::_Signal = false; // init static variable

Server::Server(int Port) : _Port(Port), _SocketFd(-1)
{
	std::cout << BLUE_BG << "Server launched" << RESET << std::endl
			  << BOLD_BLUE << "\tPort : " << RESET
			  << YELLOW_TEXT << this->Port()  << RESET << std::endl;
	while(!Server::_Signal) {
		
	}
}

//! methods

int Server::Port() const
{
	return (_Port);
}

int Server::SocketFd() const
{
	return (_SocketFd);
}

//!

void	Server::SignalHandler(int signum) {
	(void)signum;
	std::cout << RED_BG << "Signal catched\n" << RESET;
	Server::_Signal = true;
}


//?cleaning

void Server::CloseFds()
{
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
