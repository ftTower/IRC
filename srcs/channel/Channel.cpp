
#include "includes/Channel.hpp"

Channel::Channel(std::string &Name): _name(Name), topic("no topic"), password("default"), userLimit(-1) ,users(), creationTime(std::time(0)) {
        for(size_t i = 0; i < 4; i++)
                modes[i] = false;
}
