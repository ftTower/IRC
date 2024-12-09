/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 02:49:55 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 02:57:13 by tauer            ###   ########.fr       */
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




