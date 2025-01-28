

#include "includes/Server.hpp"

// verifier si le channel exist
bool Server::channelExist(std::string name)
{
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i].getChanName() == name)
		{
			return true;
		}
	}
	return false;
}

// get channel avec son nom
Channel &Server::getChan(std::string name)
{
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i].getChanName() == name)
			return channels[i];
	}
	throw(std::runtime_error("Channel not found"));
}

// ajouter un channel au vector
void Server::addChannel(Channel chan)
{
	this->channels.push_back(chan);
}

void Server::addClientToChannel(int fd, std::string channel)
{
	try
	{
		this->getChan(channel).addClient(this->findClientFd(fd));
	}
	catch (std::exception &e)
	{
		std::cerr << "Channel error, (addClientToChannel) : " << e.what() << std::endl;
	}
}