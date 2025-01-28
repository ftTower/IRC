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
#include "../../server/includes/Server.hpp"
#include <limits>

//!Base

Client::Client(int serverSock) : _nickName("default") , _fd(-1) , _serverSock(serverSock), nbPing(0) {
}

Client::~Client() {}

bool Client::operator!=(const Client &other) const {
    if (this->Fd() != other.Fd())
        return (true);
    return (false);
}


//? setters

void	Client::setFd(const int fd) {
	this->_fd = fd;
}

void	Client::setIPadd(const std::string &IPadd) {
	this->_IPadd = IPadd;
}

void		Client::setNickname(std::string name){
	this->_nickName = name;
}

void		Client::setRealName(std::string name){
	this->_realName = name;
}

void		Client::setNbPingUp() {
    if (this->nbPing < std::numeric_limits<unsigned long>::max())
        this->nbPing += 1;
}


//? getters

int		Client::ServerSock() const {
	return (this->_serverSock);
}

int		Client::Fd() const {
	return (this->_fd);
}

std::string	Client::IPadd() const {
	return (this->_IPadd);
}

std::string Client::nickName() const {
	return (this->_nickName);
}

std::string Client::realName() const{
	return (this->_realName);
}

unsigned long  Client::getNbPing() const {
    return (this->nbPing);
}

// listen

void	Client::ReceiveMessage()  {
    char buffer[1024];
    int bytesReceived = recv(this->Fd(), buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Message reçu : " << buffer << std::endl;
    } else if (bytesReceived == 0) {
        std::cout << "Le serveur a fermé la connexion." << std::endl;
    } else {
        std::cerr << "Erreur lors de la réception du message !" << std::endl;
    }
}
