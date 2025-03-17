#include "includes/Client.hpp"
#include "../../server/includes/Server.hpp"

//! channels

void		Client::addChannelToList(const std::string &c) {
    channelsList.push_back(c);
}

void		Client::removeChannelToList(std::string &c) {
    for(size_t i = 0; i < channelsList.size(); i++) {
        if (channelsList[i] == c)
            channelsList.erase(channelsList.begin() + i);
    }
}

//! messages

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

//! historic

void		Client::addCmdToHistoric(const std::string &cmd) {
    historic.push_back(cmd);
}


//! authentication

void		Client::setAuthenticated(bool toSet) {
    _authenticated = toSet;
}

