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


bool Channel::isClientOperator(Client &newOperator) {
    for (size_t i = 0; i < operators.size(); i++) {
        if (operators[i].Fd() == newOperator.Fd())
            return (true);
    }
    return (false);
}
