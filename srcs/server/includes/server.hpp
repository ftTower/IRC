/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:25 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 01:48:50 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utils/includes/colors.hpp"
#include "../../utils/includes/errMsg.hpp"
#include "../../client/includes/client.hpp"

#include <iostream>

#include <vector>


#include <errno.h>
#include <stdexcept>
#include <string>

#include <stdlib.h>
#include <poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#include <csignal>

class Server {
	
	private :
		int	_Port;
		int _SocketFd;
		
		static bool _Signal;

		std::vector<Client> clients;
		std::vector<struct pollfd> fds;

	public :
		//! constructors
		Server(int Port);

		//! methods
		void	Init();
		void	Run();

		//! getters
		int	Port() const;
		int SocketFd() const;
		
		//!signal
		static void SignalHandler(int signum);

		//?cleaning
		void	CloseFds();
		void	ClearClients(int fd);

};

void throwSocketOptionError(int socketOptionRet, std::string optionType);
