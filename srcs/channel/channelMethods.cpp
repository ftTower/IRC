#include "../includes/Server.hpp"


//! clients

void Channel::addClient(Client &newClient) {
    for (size_t i = 0;i < users.size(); i++){
        if (users[i].Fd() == newClient.Fd())
            throw (std::runtime_error("User already connected."));
    }
    users.push_back(newClient);
}

void  Channel::kickClient(int fd) {
    for(std::vector<Client>::iterator it = users.begin(); it != users.end(); ++it) {
        if (it->Fd() == fd) {
            users.erase(it);
            break;
        }
    }
}

