

#include <iomanip>
#include "includes/Server.hpp"

void	Server::initMessage() {
std::cout 	<< getTimestamp()
			<< GREEN_BG 
			<< "\tSERVER  ON "
			<< RESET
			<< std::endl
			//<< BOLD_MAGENTA
			//<< "\t\tPort : " 
			//<< RESET
			//<< LIGHT_YELLOW
			//<< this->Port()
			//<< RESET
			////<< std::endl
			//<< BOLD_MAGENTA
			//<< "\t\tSocket Fd : "
			//<< RESET
			//<< LIGHT_YELLOW
			//<< this->SocketFd()
			//<< RESET
			<< std::endl
			<< std::endl;
}

void	Server::connectedMessage(int incomingFd) {
	std::cout 	<< WHITE_BG
				<< getTimestamp()
				<< RESET
				<< GREEN_BG
				<< " Client "
				<< incomingFd
				<< " Connected !"
				<< RESET
				<< std::endl;
	usersMessage();
}

void	Server::disconnectedMessage(int fd) {
	std::cout 	<< WHITE_BG
				<< getTimestamp()
				<< RESET
				<< RED_BG
				<< " Client "
				<< fd
				<< " Disconnected !"
				<< RESET
				<< std::endl;
}

std::string formatString(const std::string &string, size_t length) {
	std::string ret = string;
	if (ret.length() > length) 
			ret = ret.substr(0, length);
	else if (ret.length() < length) {
		ret.insert(ret.end(), length - ret.length(), ' ');
	}
	return (ret);
}

std::string formatHistoric(std::vector<std::string> historic, size_t length) {
	std::string tmp;
	
	if (historic.empty())
		return (formatString(" ", length));
	for (size_t i = historic.size(); i > 0; i--) {
		tmp += formatString(historic[i - 1], 4);
		tmp += ","; 
	}
	return (formatString(tmp, length));
}

void	Server::usersMessage() {
    std::cout 	<< std::endl
				<< WHITE_BG
				<< getTimestamp()
				<< RESET
				<< YELLOW_BG
				<< "\tUSERS CONNECTED |   CONNECTION TIME   | PONG COUNTER |   LAST COMMANDS     "  
				<< RESET
				<< std::endl;
	for(size_t i = 0; i < clients.size() && i < 6; i++) {
		
		std::time_t connectTime = clients[clients.size() - 1 - i].getConnectTime();
		std::tm *ptm = std::localtime(&connectTime);
		char buffer[32];
		std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);

		
		
		std::cout 	<< "\t\t"
							//<< clients[clients.size() - 1 - i].Fd()
							//<< " "
							<< formatString(clients[clients.size() - 1 - i].nickName(), 15)
							<< " | "
							<< buffer
							<< " | "
							<< std::setw(11) << clients[clients.size() - 1 - i].getNbPing()
							<< "  | ["
							<< formatHistoric(clients[clients.size() - 1 - i].getHistoric(), 18)
							<< "]"
							<< std::endl;
	}
	std::cout << std::endl;
}




