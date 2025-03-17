#include "includes/Client.hpp"

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

std::time_t Client::getConnectTime() const {
    return (this->connect_time);
}

std::vector<std::string> Client::getHistoric() const {
    return (this->historic);
}

std::vector<std::string> Client::getChannelList() const {
    return (this->channelsList);
}

bool		Client::getAuthenticated() const {
    return (this->_authenticated);
}

