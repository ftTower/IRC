/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:25 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 23:02:37 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utils/includes/colors.hpp"
#include "../../client/includes/client.hpp"

#include <iostream>

#include <vector>

#include <stdlib.h>
#include <poll.h>
#include <unistd.h>

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
		int	Port() const;
		int SocketFd() const;
		
		static void SignalHandler(int signum);

		//?cleaning
		void	CloseFds();
		void	ClearClients(int fd);

};