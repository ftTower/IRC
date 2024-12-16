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

#include "includes/client.hpp"

//!Base

Client::Client() : _nickName("default") , _fd(-1) {
}

Client::~Client() {}

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


//? getters

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



