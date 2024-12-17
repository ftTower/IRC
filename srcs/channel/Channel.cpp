
#include "includes/Channel.hpp"



Channel::Channel(std::string &Name): _name(Name) {
	
}



Channel::~Channel() {
	
}
//// getter

std::string	Channel::getChanName(void){
    return(this->_name);
}
