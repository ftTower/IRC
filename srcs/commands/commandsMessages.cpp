

#include "./includes/Commands.hpp"
#include "../server/includes/Server.hpp"

void	Server::nickMessage(int fd, const Client &client) {
	std::cout 	<< GREEN_BG
				<< BOLD_GREEN
				<< "Client "
				<< RESET
				<<  GREEN_BG
				<< BOLD_YELLOW
				<< fd
				<< " "
				<< client.nickName()
				<< RESET
				<< GREEN_BG
				<< " Named !"
				<< RESET
				<< std::endl;
}

void	Server::pongMessage(int fd) {
	std::cout 	<< YELLOW_BG
				<< BOLD_YELLOW
				<< "PONGED CLIENT "
				<< fd
				<< RESET
				<< std::endl;
}
