#include "../includes/Server.hpp"

void Channel::addClient(Client &newClient) {
    for (size_t i = 0;i < users.size(); i++){
        if (users[i].Fd() == newClient.Fd())
            throw (std::runtime_error("User already connected."));
    }
    users.push_back(newClient);
}

void Channel::addOperator(Client &newClient) {
    operators.push_back(newClient);
}

//! modes

// typedef enum e_mode
// {
// 	MODE_INVITE,
// 	MODE_TOPIC,
// 	MODE_KEY,
// 	MODE_OP,
// } t_mode;

//? active ou desactive (true/false), un mode (t_mode) pour un channel

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