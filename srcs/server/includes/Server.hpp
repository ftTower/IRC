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

		//! methods
		void	Init();
		void	Run();
		
		//! server handler
		void	ReceiveNewData(int fd);
		void	HandleNewData(int fd, std::string &Data);
		void	HandleNick(int fd, const std::string &Data);
		
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
		bool	isNickUsed(std::string name);
		bool	channelExist(std::string name);
		Channel	&getChan(std::string name);
		void	addChannel(Channel chan);

};

void throwSocketOptionError(int socketOptionRet, std::string optionType);
