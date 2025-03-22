#include "../includes/Server.hpp"

//! getters

std::vector <Client> Channel::getUsersList() {
    return (this->users);
}

std::vector<Client> Channel::getOperatorsList(void) {
    return (this->operators);
}

std::vector<Client> Channel::getInvitationsList(void) {
    return (this->invitations);
}


std::string	Channel::getChanName(void){
    return(this->_name);
}

std::string Channel::getTopic(void) {
    return (this->topic);
}

std::string 		Channel::getPassword(void) {
    return (this->password);
}


std::time_t Channel::getCreationTime(void) {
    return(this->creationTime);
}

bool* Channel::getModes() {
    return (this->modes);
}