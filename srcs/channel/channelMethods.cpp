#include "../includes/Server.hpp"

void  Channel::kickClient(int fd) {
    for(std::vector<Client>::iterator it = users.begin(); it != users.end(); ++it) {
        if (it->Fd() == fd) {
            users.erase(it);
            break;
        }
    }
}

void Channel::kickOperator(int fd) {
    for(std::vector<Client>::iterator it = operators.begin(); it != operators.end(); ++it) {
        if (it->Fd() == fd) {
            operators.erase(it);
            break;
        }
    }
}

void Channel::kickInvitation(int fd) {
    for(std::vector<Client>::iterator it = invitations.begin(); it != invitations.end(); ++it) {
        if (it->Fd() == fd) {
            invitations.erase(it);
            break;
        }
    }
}

bool Channel::isClientConnected(Client &Client) {
    for (size_t i = 0; i < users.size(); i++) {
        if (Client.Fd() == users[i].Fd())
            return (true);
    }
    return (false);
}


bool Channel::isClientOperator(Client &newOperator) {
    for (size_t i = 0; i < operators.size(); i++) {
        if (operators[i].Fd() == newOperator.Fd())
            return (true);
    }
    return (false);
}

bool Channel::isClientInvited(Client &newOperator) {
    for (size_t i = 0; i < invitations.size(); i++) {
        if (invitations[i].Fd() == newOperator.Fd())
            return (true);
    }
    return (false);
}
