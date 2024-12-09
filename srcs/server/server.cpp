/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:44:30 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 03:35:17 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/server.hpp"
#include <algorithm>

bool Server::_Signal = false; // init static variable

Server::Server(int Port) : _Port(Port), _SocketFd(-1)
{
}

//! methods

void Server::Init()
{
	struct sockaddr_in	add;
	struct pollfd		NewPoll;
	int					en;

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
	std::cout << GREEN_BG << BOLD_WHITE << " SERVER ON " << RESET << std::endl << BOLD_MAGENTA << "\tPort : " << RESET << LIGHT_YELLOW << this->Port() << RESET << std::endl << BOLD_MAGENTA << "\tSocket Fd : " << RESET << LIGHT_YELLOW << this->SocketFd() << RESET << std::endl << std::endl;
	
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
	Client C;

	struct sockaddr_in CliAdd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(CliAdd);
	
	int incomingFd = accept(SocketFd(), (sockaddr *)&(CliAdd), &len);
	if (incomingFd == -1)
		{std::cout << "\t\t" << RED_BG << BOLD_RED << "failed to accept" << RESET << std::endl; return;}
	if (fcntl(incomingFd, F_SETFL, O_NONBLOCK) == -1)
		{std::cout << "\t\t" << RED_BG << BOLD_RED << "failed to fcntl" << RESET << std::endl; return;}
	
	NewPoll.fd = incomingFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;

	C.setFd(incomingFd);
	C.setIPadd(inet_ntoa((CliAdd.sin_addr)));
	
	clients.push_back(C);
	fds.push_back(NewPoll);

	std::cout << "\t\t\t\t\t\t" << GREEN_BG << BOLD_GREEN << "Client "  << RESET <<  GREEN_BG << BOLD_YELLOW << incomingFd << RESET << GREEN_BG << " Connected !" << RESET << std::endl;
	
}

void	Server::kickClient(int fd) {
	std::cout << "\t\t\t\t\t\t" << RED_BG << BOLD_RED << "Client " << RESET << RED_BG << BOLD_YELLOW << fd << RESET << RED_BG << " Disconnected !" << RESET << std::endl;
		ClearClients(fd);
		close(fd);
}

void	Server::PongClient(int fd) {
	const char *Pong = "PONG localhost\n";
	std::cout << "\t\t\t\t\t\t" << YELLOW_BG << BOLD_YELLOW "PONGED CLIENT " << fd << RESET << std::endl;
	send(fd, Pong, strlen(Pong), 0);
}

std::string Server::remove(const std::string &Data, char c) {
	std::string ret = "";
	for (size_t i = 0; i < Data.size(); i++) {
		if (Data[i] != c)
			ret += Data[i];
	}
	return (ret);
}

void	Server::HandleNick(int fd, const std::string &Data) {
	(void)Data;
	
	std::string Nickname = Data.substr(Data.find("NICK") + 5);
	Nickname = Nickname.substr(0, Nickname.find("\r\n"));
	for(size_t i = 0; i < clients.size(); i++) {
		if (clients[i].nickName() == Nickname) {
			std::string error = ":server 433 * " + Nickname + " :Nickname is already in use\r\n";
			send(fd, error.c_str(), error.size(), 0);
			return ;
		}
	}
	clients[fd].nickName() = Nickname;
	std::string welcome = ":server 001 " + Nickname + " :Welcome to the IRC server\r\n";
	send(fd, welcome.c_str(), welcome.size(), 0);
	std::cout << "\t\t\t\t\t\t" << GREEN_BG << BOLD_GREEN << "Client "  << RESET <<  GREEN_BG << BOLD_YELLOW << fd << " " <<  Nickname << RESET << GREEN_BG << " Named !" << RESET << std::endl;
}

void	Server::HandleNewData(int fd, std::string &Data) {
	
		if (Data.find("\r\n") != std::string::npos) {
			std::cout << YELLOW_BG << BOLD_YELLOW << "Client " << RESET << YELLOW_BG << BOLD_RED << fd << " Data :" << RESET
			<< "\n" << Data;   
			if (Data.find("PING") != std::string::npos)
				PongClient(fd);
			else if (Data.find("NICK") != std::string::npos)
				HandleNick(fd, Data);
		}
		//strBuff.erase(std::remove_if(strBuff.begin(), strBuff.end(), isspace), strBuff.end());
}


void Server::ReceiveNewData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	
	if (bytes <= 0)
		kickClient(fd);
	else {
		buff[bytes] = '\0';
		std::string strBuff(buff);
		HandleNewData(fd, strBuff);
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
			break ;
		}
}
