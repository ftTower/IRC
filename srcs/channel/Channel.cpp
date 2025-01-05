
#include "includes/Channel.hpp"



Channel::Channel(std::string &Name): _name(Name), users() {
	for(size_t i = 0; i < 4; i++)
        modes[i] = false;
}

void Channel::addClient(Client &newClient) {
    users.push_back(newClient);
}


//Channel::~Channel() {
	
//}

//// getter

std::string	Channel::getChanName(void){
    return(this->_name);
}
