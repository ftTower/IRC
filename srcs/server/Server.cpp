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

Server::Server(int Port) : _Port(Port), _SocketFd(-1), clients(), channels()
{
}

//! methods

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
	std::cout << GREEN_BG << BOLD_WHITE << " SERVER ON " << RESET << std::endl
			  << BOLD_MAGENTA << "\tPort : " << RESET << LIGHT_YELLOW << this->Port() << RESET << std::endl
			  << BOLD_MAGENTA << "\tSocket Fd : " << RESET << LIGHT_YELLOW << this->SocketFd() << RESET << std::endl
			  << std::endl;

	while (!Server::_Signal)
	{
		if ((poll(&fds[0], fds.size(), -1) == -1) && Server::_Signal == false)
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
	}
	CloseFds();
}

void Server::AcceptNewClient()
{
	Client C(_SocketFd);

	struct sockaddr_in CliAdd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(CliAdd);

	int incomingFd = accept(SocketFd(), (sockaddr *)&(CliAdd), &len);
	if (incomingFd == -1)
	{
		std::cout << "\t\t" << RED_BG << BOLD_RED << "failed to accept" << RESET << std::endl;
		return;
	}
	if (fcntl(incomingFd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "\t\t" << RED_BG << BOLD_RED << "failed to fcntl" << RESET << std::endl;
		return;
	}

	NewPoll.fd = incomingFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;

	C.setFd(incomingFd);
	C.setIPadd(inet_ntoa((CliAdd.sin_addr)));

	clients.push_back(C);
	fds.push_back(NewPoll);

	std::cout << "\t\t\t\t\t\t" << GREEN_BG << BOLD_GREEN << "Client " << RESET << GREEN_BG << BOLD_YELLOW << incomingFd << RESET << GREEN_BG << " Connected !" << RESET << std::endl;
}

void Server::kickClient(int fd)
{
	std::cout << "\t\t\t\t\t\t" << RED_BG << BOLD_RED << "Client " << RESET << RED_BG << BOLD_YELLOW << fd << RESET << RED_BG << " Disconnected !" << RESET << std::endl;
	ClearClients(fd);
	close(fd);
}

std::string Server::remove(const std::string &Data, char c)
{
	std::string ret = "";
	for (size_t i = 0; i < Data.size(); i++)
	{
		if (Data[i] != c)
			ret += Data[i];
	}
	return (ret);
}

void Server::sendMessage(std::vector<std::string> &target, const std::string &msg, const Client &sender) {
    std::vector<Client> sendList;

    for (size_t i = 0; i < target.size(); i++) {
        if (!this->channels.empty() && this->channelExist(target[i])) {
            std::vector<Client> buf = this->getChan(target[i]).getUsersList();
            sendList.insert(sendList.end(), buf.begin(), buf.end());
        } else {
            target[i] = target[i].substr(1); // Retirer le '#' pour les canaux privés
            sendList.push_back(this->findClientNick(target[i]));
        }
    }

    // Construire le message formaté
    std::string formattedMsg = ":" + sender.nickName() + "!" + sender.nickName() + "@localhost PRIVMSG ";
    formattedMsg += target[0] + " :" + msg + "\r\n";

    // Envoyer le message à tous les destinataires
    for (size_t i = 0; i < sendList.size(); i++) {
        ssize_t bytesSent = send(sendList[i].Fd(), formattedMsg.c_str(), formattedMsg.size(), 0);
        if (bytesSent < 0) {
            std::cerr << "Failed to send message to client: " << sendList[i].Fd() << "\n";
            kickClient(sendList[i].Fd());
        }
    }
}

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

//! getters

int Server::Port() const
{
	return (_Port);
}

int Server::SocketFd() const
{
	return (_SocketFd);
}

std::vector<Channel> Server::getChannelList()
{
	return (this->channels);
}

//! signal

void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << "\033[2K";
	Server::_Signal = true;
}

//?cleaning

void Server::CloseFds()
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		std::cout << "\t\t\t\t\t\t" << RED_BG << BOLD_RED << "Client " << RESET << RED_BG << BOLD_YELLOW << clients[i].Fd() << RESET << RED_BG << " Disconnected !" << RESET << std::endl;
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
			break;
		}
}

///// test commands

// trouver un client dans le vector des clients via son fd
Client &Server::findClientFd(int fd)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].Fd() == fd)
			return clients[i];
	}
	throw std::runtime_error("Client not found");
}

// trouver un client dans le vector des clients via son nick
Client &Server::findClientNick(std::string nick)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].nickName() == nick)
			return clients[i];
	}
	throw std::runtime_error(nick);
}
bool Server::isNickUsed(std::string name, int fd)
{
	if (this->channelExist(name))
		return true;
	for (size_t i = 0; i < this->clients.size(); i++)
		if (this->clients[i].nickName() == name && this->clients[i].Fd() != fd)	
			return true;
	return false;
};

//////////////////////////////CHANNEL RELATED/////////////////////////////////

// verifier si le channel exist
bool Server::channelExist(std::string name)
{
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i].getChanName() == name)
		{
			return true;
		}
	}
	return false;
}

// get channel avec son nom
Channel &Server::getChan(std::string name)
{
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i].getChanName() == name)
			return channels[i];
	}
	throw(std::runtime_error("Channel not found"));
}

// ajouter un channel au vector
void Server::addChannel(Channel chan)
{
	this->channels.push_back(chan);
}

void Server::addClientToChannel(int fd, std::string channel)
{
	try
	{
		this->getChan(channel).addClient(this->findClientFd(fd));
	}
	catch (std::exception &e)
	{
		std::cerr << "Channel error, (addClientToChannel) : " << e.what() << std::endl;
	}
}
