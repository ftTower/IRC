#include "../includes/Server.hpp"

//! getters

std::vector <Client> Channel::getUsersList() {
    return (this->users);
}

std::vector<Client> Channel::getOperatorsList(void) {
    return (this->operators);
}

std::string	Channel::getChanName(void){
    return(this->_name);
}

std::string Channel::getTopic(void) {
    return (this->topic);
}

std::time_t Channel::getCreationTime(void) {
    return(this->creationTime);
}

bool* Channel::getModes() {
    return (this->modes);
}