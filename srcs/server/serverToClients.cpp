

#include "includes/Server.hpp"

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

	std::cout << "\t\t\t\t\t\t" << GREEN_BG << BOLD_GREEN << "Client " << RESET << GREEN_BG << BOLD_YELLOW << incomingFd << RESET << GREEN_BG << " Connected !" << RESET << std::endl;
}

void Server::kickClient(int fd)
{
	std::cout << "\t\t\t\t\t\t" << RED_BG << BOLD_RED << "Client " << RESET << RED_BG << BOLD_YELLOW << fd << RESET << RED_BG << " Disconnected !" << RESET << std::endl;
	ClearClients(fd);
	close(fd);
}

void Server::sendMessage(std::vector<std::string> &target, const std::string &msg, const Client &sender) {
    std::vector<Client> sendList;

    for (size_t i = 0; i < target.size(); i++) {
        if (!this->channels.empty() && this->channelExist(target[i])) {
            std::vector<Client> buf = this->getChan(target[i]).getUsersList();
            sendList.insert(sendList.end(), buf.begin(), buf.end());
        } else {
            try {
				if (target[i][0] == '"')
					target[i] = target[i].substr(1); // Retirer le '#' pour les canaux privés
				sendList.push_back(this->findClientNick(target[i]));	
			} catch (std::exception &e) {
				std::cerr << "FAILED TO FIND CLIENT NAMED :" << e.what() << std::endl;
			}
        }
    }

    // Construire le message formaté
    std::string formattedMsg = ":" + sender.nickName() + "!" + sender.nickName() + "@localhost PRIVMSG ";
	formattedMsg += target[0] + " :" + msg + "\r\n";

    // Envoyer le message à tous les destinataires
    for (size_t i = 0; i < sendList.size(); i++) {
		if (sendList[i] != sender) {
			ssize_t bytesSent = send(sendList[i].Fd(), formattedMsg.c_str(), formattedMsg.size(), 0);
			if (bytesSent < 0) {
				std::cerr << "Failed to send message to client: " << sendList[i].Fd() << "\n";
				kickClient(sendList[i].Fd());
			}
		}
    }
}

