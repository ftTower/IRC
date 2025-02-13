
#include "includes/Server.hpp"


int Server::Port() const
{
	return (_Port);
}

int Server::SocketFd() const
{
	return (_SocketFd);
}

std::vector<Channel> Server::getChannelList()
{
	return (this->channels);
}

std::string Server::getPassword() const {
	return (this->_password);
}

bool		Server::getPass() const {
	return (this->_pass);
}