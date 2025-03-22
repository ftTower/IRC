
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

std::vector<std::string> Server::getErrors() {
	return (errors);
}


std::string Server::getPassword() const {
	return (this->_password);
}

bool		Server::getPass() const {
	return (this->_pass);
}

std::vector<Client> Server::getAllClients() {
	std::vector<Client> vec;
	
	for (size_t i = 0; i < channels.size(); i++) {
		std::vector<Client> users = channels[i].getUsersList();
		vec.insert(vec.end(), users.begin(), users.end());
	}
	return (vec);
}
