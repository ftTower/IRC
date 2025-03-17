

#include <iomanip>
#include "includes/Server.hpp"

#include <fstream>

void writeToFile(const std::string &filename, const std::string &content) {
    std::ofstream file;
    
    //! Ouvre le fichier en mode écriture (crée s'il n'existe pas, écrase sinon)
    file.open(filename.c_str(), std::ios::out | std::ios::app);
    
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
        return;
    }
    
    file << content << std::endl;
    file.close();
}

void	closingMessage() {
	std::string buf = getTimestamp() + "\t✖️ SERVER  OFF\n";
	writeToFile("output.csv", buf);
	
	std::cout 	<< std::endl
				<< getTimestamp()
				<< RED_BG
				<< "\tSERVER DOWN"
				<< RESET
				<< std::endl;
}


void	Server::initMessage() {
std::string buf = getTimestamp() + "\t✅ SERVER  ON\n";
writeToFile("output.csv", buf);

std::cout 	<< getTimestamp()
			<< GREEN_BG 
			<< "\tSERVER  ON "
			<< RESET
			<< std::endl
			<< std::endl
			<< std::endl;
			
}

void	Server::connectedMessage(int incomingFd) {
	std::string buf = getTimestamp() + "\t\tNEW CLIENT\n";
	writeToFile("output.csv", buf);

	std::cout 	<< BLACK_BG
				<< getTimestamp()
				<< RESET
				<< "\t"
				<< GREEN_BG
				<< " Client "
				<< incomingFd
				<< " Connected !"
				<< RESET
				<< std::endl;
}

void	Server::disconnectedMessage(int fd) {
	std::string buf = getTimestamp() + "\t\tREMOVED CLIENT\n";
	writeToFile("output.csv", buf);
	
	std::cout 	<< BLACK_BG
				<< getTimestamp()
				<< RESET
				<< "\t"
				<< RED_BG
				<< " Client "
				<< fd
				<< " Disconnected !"
				<< RESET
				<< std::endl;
}

//! formate une string a partir dune size
std::string formatString(const std::string &string, size_t length) {
	std::string ret = string;
	if (ret.length() > length) 
			ret = ret.substr(0, length);
	else if (ret.length() < length) {
		ret.insert(ret.end(), length - ret.length(), ' ');
	}
	return (ret);
}

//! formate lhistoric des users pour lafficher joliment
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

//! message server qui recap les users connecte 
void	Server::usersMessage(size_t size, bool displayTime) {
    std::cout 	<< std::endl;
	if (displayTime) {
		std::cout 	<< BLACK_BG
					<< getTimestamp()
					<< RESET;
	}
	std::cout 	<< CYAN_BG
				<< "\tUSERS CONNECTED |   CONNECTION TIME   |     MODES    |   LAST COMMANDS     "  
				<< RESET
				<< std::endl;
	for(size_t i = 0; i < clients.size() && i < size; i++) {
		
		std::time_t connectTime = clients[clients.size() - 1 - i].getConnectTime();
		std::tm *ptm = std::localtime(&connectTime);
		char buffer[32];
		std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);

		
		std::cout 			<< "\t\t"
							<< formatString(clients[clients.size() - 1 - i].nickName(), 15)
							<< " | "
							<< buffer
							<< " | ";
							if (this->channels[i].getModes()[MODE_INVITE])
									std::cout << GREEN_BG << " I " << RESET;
								else 						
									std::cout << RED_BG << " I " << RESET;
								if (this->channels[i].getModes()[MODE_KEY])
									std::cout << GREEN_BG << " K " << RESET;
								else 						
									std::cout << RED_BG << " K " << RESET;
								if (this->channels[i].getModes()[MODE_OP])
									std::cout << GREEN_BG << " O " << RESET;
								else 						
									std::cout << RED_BG << " O " << RESET;
								if (this->channels[i].getModes()[MODE_TOPIC])
									std::cout << GREEN_BG << " T " << RESET;
								else 						
									std::cout << RED_BG << " T " << RESET;
		std::cout			<< " |  "
							<< formatHistoric(clients[clients.size() - 1 - i].getHistoric(), 18)
							<< std::setw(5) << clients[clients.size() - 1 - i].getNbPing()
							<< std::endl;
	}
	std::cout << std::endl;
}

//! message server qui recap les channels
void	Server::channelMessage(size_t size, bool displayTime) {
	std::cout << std::endl;
	if (displayTime) {
		std::cout 	<< BLACK_BG
					<< getTimestamp()
					<< RESET;
		
	}
	else
		std::cout << "\t";
	std::cout	<< YELLOW_BG
				<< "\t     CHANNELS   |    CREATION TIME    |     USERS    |   TOPICS            "  
				<< RESET
				<< std::endl;
	
	
	for(size_t i = 0; i < channels.size() && i < size; i++) {
		std::time_t connectTime = channels[channels.size() - 1 - i].getCreationTime();
		std::tm *ptm = std::localtime(&connectTime);
		char buffer[32];
		std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
		
		std::cout 			<< "\t\t"
							<< formatString(channels[channels.size() - 1 - i].getChanName(), 15)
							<< " | "
							<< std::setw(19)
							<< buffer;
							// << " | ";
		
		std::cout 	<< " |  "
					<< std::setw(11) << channels[channels.size() - 1 - i].getUsersList().size()
					<< " |  "
					<< formatString(channels[channels.size() - 1 - i].getTopic(), 11)
					<< std::endl;
	}
}

void Server::errorMessage(size_t size) {
	if (errors.empty())
		return ;
	std::cout << std::endl << std::endl << RED_BG << "\t\tLast errors :" << RESET << std::endl;
	for (size_t i = 0; i < errors.size() && i < size; i++) {
		if (errors[i].find("\n\r") && size > 3)
			std::cout << "\t\t\t" << errors[i].substr(0, errors[i].find("\n\r")) << std::endl;
		else
			std::cout << "\t\t\t" << errors[i] << std::endl;
	}
}

//! ensemble de la routine de message du serveur
void	Server::serverMessage() {
	std::cout << "\033c";
	usersMessage(10, true);
	channelMessage(10, false);
	errorMessage(5);
	std::cout << "\n\n";
}

