

#include "includes/Server.hpp"

void	Server::initMessage() {
std::cout 	<< GREEN_BG 
			<< "\t\t\t\tSERVER ON "
			<< RESET
			<< std::endl
			<< BOLD_MAGENTA
			<< "\t\tPort : " 
			<< RESET
			<< LIGHT_YELLOW
			<< this->Port()
			<< RESET
			//<< std::endl
			<< BOLD_MAGENTA
			<< "\t\t\tSocket Fd : "
			<< RESET
			<< LIGHT_YELLOW
			<< this->SocketFd()
			<< RESET
			<< std::endl
			<< std::endl;
}

void	Server::connectedMessage(int incomingFd) {
	std::cout 	<< GREEN_BG
				<< BOLD_GREEN
				<< "Client "
				<< RESET
				<< GREEN_BG
				<< BOLD_YELLOW
				<< incomingFd
				<< RESET
				<< GREEN_BG
				<< " Connected !"
				<< RESET
				<< std::endl;
}

void	Server::disconnectedMessage(int fd) {
	std::cout 	<< RED_BG
				<< BOLD_RED
				<< "Client "
				<< RESET
				<< RED_BG
				<< BOLD_YELLOW
				<< fd
				<< RESET
				<< RED_BG
				<< " Disconnected !"
				<< RESET
				<< std::endl;
}



