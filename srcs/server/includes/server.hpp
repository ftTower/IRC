/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:25 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 02:52:18 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utils/includes/colors.hpp"
#include "../../utils/includes/errMsg.hpp"

#include "../../client/includes/client.hpp"
#include "../../channel/includes/channel.hpp"

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

		
		//! getters
		int	Port() const;
		int SocketFd() const;
		
		//!signal
		static void SignalHandler(int signum);

		//?cleaning
		void	CloseFds();
		void	ClearClients(int fd);


		//utils
		std::string remove(const std::string &Data, char c);
		
};

void throwSocketOptionError(int socketOptionRet, std::string optionType);
