#include "includes/Client.hpp"

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