
#include "includes/Channel.hpp"



Channel::Channel(std::string &Name): _name(Name), topic("no topic"),users(), creationTime(std::time(0)) {
	for(size_t i = 0; i < 4; i++)
        modes[i] = false;
}

void Channel::addClient(Client &newClient) {
    for (size_t i = 0;i < users.size(); i++){
        if (users[i].Fd() == newClient.Fd())
            throw (std::runtime_error("User already connected."));
    }
    users.push_back(newClient);
}


//Channel::~Channel() {
	
//}

//// getter

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

void	Channel::setModes(t_mode mode, bool toSet) {
    switch (mode)
    {
        case MODE_INVITE:
            modes[MODE_INVITE] = toSet;
            break;
        case MODE_TOPIC:
            modes[MODE_TOPIC] = toSet;
        break;
        case MODE_KEY:
            modes[MODE_KEY] = toSet;
            break;
        case MODE_OP:
            modes[MODE_OP] = toSet;
        break;
        default:
            break;
    }
}

