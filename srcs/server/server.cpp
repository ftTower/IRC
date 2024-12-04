/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:44:30 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 01:57:55 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/server.hpp"

Server::Server(int Port) : _Port(Port) {
	
}

//! methods

int Server::Port() const {
	return (_Port);
}