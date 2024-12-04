/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:25 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 03:40:55 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utils/includes/colors.hpp"
#include "../../client/includes/client.hpp"

#include <iostream>
#include <vector>
#include <stdlib.h>

class Server {
	
	private :
		int	_Port;
		// int _SocketFd;
		
		static bool Signal;

		std::vector<Client> clients;
		// std::vector<struct pollfd> fds;

	public :
		Server(int Port);		

		//! methods
		int	Port() const;


};