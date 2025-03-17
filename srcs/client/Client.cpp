/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 02:49:55 by tauer             #+#    #+#             */
/*   Updated: 2024/12/16 09:20:13 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Client.hpp"

//!Base

Client::Client(int serverSock) : _nickName("default") , _fd(-1) , _serverSock(serverSock), _authenticated(false), nbPing(0), connect_time(std::time(0)) {
    for(size_t i = 0; i < 4; i++)
        modes[i] = false;
}

Client::~Client() {}

bool Client::operator!=(const Client &other) const {
    if (this->Fd() != other.Fd())
        return (true);
    return (false);
}
