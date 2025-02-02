/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:25 by tauer             #+#    #+#             */
/*   Updated: 2024/12/16 09:04:34 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utils/includes/colors.hpp"
#include "../../utils/includes/errMsg.hpp"

#include "../../client/includes/Client.hpp"
#include "../../channel/includes/Channel.hpp"
#include "../../commands/includes/Commands.hpp"


#include <iostream>
#include <algorithm>

#include <vector>


#include <errno.h>
#include <stdexcept>
#include <cstring>
#include <string.h>

#include <stdlib.h>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include <csignal>

class Server {
	
	private :
		int	_Port;
		int _SocketFd;
		
		static bool _Signal;

		std::vector<Client> clients;
		std::vector<Channel> channels;

		std::vector<struct pollfd> fds;

	public :
		//! constructors
		Server(int Port);

		//! messages
		void	closingMessage();
		void	initMessage();
		void	connectedMessage(int incomingFd);
		void	disconnectedMessage(int fd);
		
		//? commands messages
		void	cmdParseMessage(int fd, Server &serv, std::vector<std::string> commands);
		void	nickMessage(int fd, const Client &client);
		void	pongMessage(int fd);
		//? routine messages
		void	usersMessage(size_t size, bool displayTime);
		void	channelMessage(size_t size, bool displayTime);
			
		//! methods
		void	Init();
		void	Run();
		
		//! server handler
		void	ReceiveNewData(int fd);
		void	HandleNewData(int fd, std::string &Data);
		void	HandleNick(int fd, const std::string &Data);
		
		void 	sendMessage(std::vector<std::string> &target, const std::string &msg, const Client &sender);


		//! Client
		void	AcceptNewClient();
		void	kickClient(int fd);
		void	PongClient(int fd);
		void	addClientToChannel(int fd, std::string channel);

		
		//! getters
		int	Port() const;
		int SocketFd() const;
		std::vector<Channel> getChannelList();

		//!signal
		static void SignalHandler(int signum);

		//?cleaning
		void	CloseFds();
		void	ClearClients(int fd);


		//! utils
		std::string remove(const std::string &Data, char c);
		
		//! Commands utils
		Client &findClientFd(int fd);
		Client &findClientNick(std::string nick);
		bool	isNickUsed(std::string name, int fd);
		bool	channelExist(std::string name);
		Channel	&getChan(std::string name);
		void	addChannel(Channel chan);


};

void writeToFile(const std::string &filename, const std::string &content);
void throwSocketOptionError(int socketOptionRet, std::string optionType);

std::string getTimestamp();