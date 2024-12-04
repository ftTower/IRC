/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:25 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 01:53:33 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>

class Client;

class Server {
	
	private :
		int	_Port;


	public :
		Server(int Port);		

		//! methods
		int	Port() const;


};