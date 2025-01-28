

#include "includes/Server.hpp"

//accepter un client sur le serveur
void Server::AcceptNewClient()
{
	Client C(_SocketFd);

	struct sockaddr_in CliAdd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(CliAdd);

	int incomingFd = accept(SocketFd(), (sockaddr *)&(CliAdd), &len);
	if (incomingFd == -1)
	{
		std::cout << "\t\t" << RED_BG << BOLD_RED << "failed to accept" << RESET << std::endl;
		return;
	}
	if (fcntl(incomingFd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "\t\t" << RED_BG << BOLD_RED << "failed to fcntl" << RESET << std::endl;
		return;
	}

	NewPoll.fd = incomingFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;

	C.setFd(incomingFd);
	C.setIPadd(inet_ntoa((CliAdd.sin_addr)));

	clients.push_back(C);
	fds.push_back(NewPoll);

	connectedMessage(incomingFd);
}

// deconnecter un client
void Server::kickClient(int fd)
{
	disconnectedMessage(fd);
	ClearClients(fd);
	close(fd);
}

// deconnecter tout les clients
void Server::ClearClients(int fd)
{
	for (size_t i = 0; i < fds.size(); i++)
		if (fds[i].fd == fd)
			fds.erase(fds.begin() + i);
	for (size_t i = 0; i < clients.size(); i++)
		if (clients[i].Fd() == fd)
		{
			clients.erase(clients.begin() + i);
			break;
		}
}

// trouver un client dans le vector des clients via son fd
Client &Server::findClientFd(int fd)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].Fd() == fd)
			return clients[i];
	}
	throw std::runtime_error("Client not found");
}

// trouver un client dans le vector des clients via son nick
Client &Server::findClientNick(std::string nick)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].nickName() == nick)
			return clients[i];
	}
	throw std::runtime_error(nick);
}
bool Server::isNickUsed(std::string name, int fd)
{
	if (this->channelExist(name))
		return true;
	for (size_t i = 0; i < this->clients.size(); i++)
		if (this->clients[i].nickName() == name && this->clients[i].Fd() != fd)	
			return true;
	return false;
};

