/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:53:49 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 01:56:06 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Server.hpp"

//? a gerer plus tard - tower
void	throwSocketOptionError(int socketOptionRet, std::string optionType)
{
	if (socketOptionRet == -1)
	{
		switch (errno)
		{
		case EBADF:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EBADF);
		case EDOM:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EDOM);
		case EINVAL:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EINVAL);
		case EISCONN:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EISCONN);
		case ENOPROTOOPT:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOPROTOOPT);
		case ENOTSOCK:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOTSOCK);
		case ENOMEM:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOMEM);
		case ENOBUFS:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOBUFS);
		default:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + "Unknown socket option error");
		}
	}
}

//! signal
void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << "\033[2K\033[0G";
	Server::_Signal = true;
}

//?cleaning
void Server::CloseFds()
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		disconnectedMessage(clients[i].Fd());
		if (clients[i].Fd() >= 0)
			close(clients[i].Fd());
	}
}

//! error
void Server::addError(std::string error) {
	errors.push_back(error);
}

//! time
#include <iostream>
#include <ctime>
#include <sstream>

std::string getTimestamp() {
    std::time_t now = std::time(0);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "[%H:%M:%S]", std::localtime(&now));
    return std::string(buffer);
}

bool shouldTriggerEveryXSeconds(int x) {
    static std::time_t lastTrigger = std::time(NULL);
    std::time_t now = std::time(NULL);
    
    if (now - lastTrigger >= x) {
        lastTrigger = now;
        return true;
    }
    return false;
}

void Send(int fd, std::string reply) {
	ssize_t sent = send(fd, reply.c_str(), reply.length(), 0);
	if (sent == -1) {
		std::ostringstream oss;
		oss << fd << " failed to send " << reply << "\n";
		std::string error = oss.str();
		throw(std::runtime_error(error));
	}
}
