

#include "./includes/Commands.hpp"
#include "../server/includes/Server.hpp"

void	Server::cmdParseMessage(int fd, Server &serv, std::vector<std::string> commands) {
	//std::cout 	<< BLACK_BG
	//			<< getTimestamp()
	//			<< RESET
	//			<< MAGENTA_BG
	//			<< " Client "
	//			<< fd
	//			<< " "
	//			<< serv.findClientFd(fd).nickName()
	//			<< " Data : "
	//			<< RESET; 
	
	//! afficher toute la cmd 
	//for (unsigned long int i = 0; i != commands.size(); i++){
	//	std::cout << commands[i] << " ";
	//}
	//? afficher seulement cmd[0]
	//if (!commands.empty()) {
	//	std::cout << MAGENTA_BG;
	//	if (!commands[0].empty()) {
	//		for(size_t i = 0; i < commands[0].size(); i++) {
	//			if (commands[0][i] == '\n' || commands[0][i] == '\r')
	//				break;
	//			std::cout << commands[0][i];
	//		}
	//	}
	//	std::cout << RESET << std::endl;
	//}
	//std::cout << std::endl;
	(void)fd;
	(void)serv;
	(void)commands;
}



void	Server::nickMessage(int fd, const Client &client) {
	//std::cout 	<< BLACK_BG
	//			<< getTimestamp()
	//			<< RESET
	//			<< GREEN_BG
	//			<< " Client "
	//			<< fd
	//			<< " "
	//			<< client.nickName()
	//			<< " Named !"
	//			<< RESET
	//			<< std::endl;
	(void)fd;
	(void)client;
}

void	Server::pongMessage(int fd) {
	//std::cout 	<< YELLOW_BG
	//			<< BOLD_YELLOW
	//			<< "PONGED CLIENT "
	//			<< fd
	//			<< RESET
	//			<< std::endl;
	(void)fd;
}
