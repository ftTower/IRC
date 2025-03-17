
#include "includes/Channel.hpp"

Channel::Channel(std::string &Name): _name(Name), topic("no topic"),users(), creationTime(std::time(0)) {
	
}
