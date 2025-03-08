#include "../includes/Server.hpp"

//! getters

std::vector <Client> Channel::getUsersList() {
    return (this->users);
}

std::string	Channel::getChanName(void){
    return(this->_name);
}

std::string Channel::getTopic(void) {
    return (this->topic);
}

bool* Channel::getModes() {
    return (this->modes);
}

std::time_t Channel::getCreationTime(void) {
    return(this->creationTime);
}