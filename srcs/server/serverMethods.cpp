#include "includes/Server.hpp"

//! recupere une commande ou kick le client
void Server::ReceiveNewData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);

	if (bytes <= 0)
		kickClient(fd);
	else
	{
		buff[bytes] = '\0';
		handleCmds(*this, fd, buff); //? parseur de commandes
	}
}

//! envoyer un message a un vecteur de target
void Server::sendMessage(std::vector<std::string> &target, const std::string &msg, const Client &sender) {
    std::vector<Client> sendList;

	if (target.empty())
		return ;
	
	//? cherche dans les targets donnees si ils sont simple client ou channels
    for (size_t i = 0; i < target.size(); i++) {
		
		target[i].erase(std::remove_if(target[i].begin(), target[i].end(), ::isspace), target[i].end()); //enlever les whitesspaces superflux
		
		//? est ce un channel ? si oui, insertion des users du clients dans ma sending list
        if (!this->channels.empty() && target[i][0] == '#' && this->channelExist(target[i])) {
            std::vector<Client> buf = this->getChan(target[i]).getUsersList();
            sendList.insert(sendList.end(), buf.begin(), buf.end());
		} else {	//? sinon je push le client
            try {
				sendList.push_back(this->findClientNick(target[i]));	
			} catch (std::exception &e) {
				std::cerr << "\t\t" << RED_BG << sender.nickName() << " sent to a unknown user named [" << e.what() << "] ?" << RESET <<  std::endl;
			}
        }
    }

    //? Construire le message formaté
    std::string formattedMsg = ":" + sender.nickName() + "!" + sender.nickName() + "@localhost PRIVMSG ";
	formattedMsg += target[0] + " :" + msg + "\r\n";

    //? Envoyer le message à toutes la sendlist
    for (size_t i = 0; i < sendList.size(); i++) {
		if (sendList[i] != sender) {
			ssize_t bytesSent = send(sendList[i].Fd(), formattedMsg.c_str(), formattedMsg.size(), 0);
			if (bytesSent < 0) {
				std::cerr << "Failed to send message to client: " << sendList[i].Fd() << "\n";
				kickClient(sendList[i].Fd());
			}
		}
    }
}

void Server::Init()
{
	struct sockaddr_in add;
	struct pollfd NewPoll;
	int en;

	add.sin_family = AF_INET;
	add.sin_port = htons(this->Port());
	add.sin_addr.s_addr = INADDR_ANY;
	_SocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFd() == -1)
		throwSocketOptionError(-1, ERR_SOCKET);
	en = 1;
	if (setsockopt(SocketFd(), SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throwSocketOptionError(-1, ERR_SOCKET_OPTION_R);
	if (fcntl(SocketFd(), F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error(ERR_SOCKET_OPTION_N));
	if (bind(SocketFd(), (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error(ERR_SOCKET_BIND));
	if (listen(SocketFd(), SOMAXCONN) == -1)
		throw(std::runtime_error(ERR_SOCKET_LISTEN));
	NewPoll.fd = SocketFd();
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);
}

void Server::Run()
{
	Init();
	initMessage();

	//! tant que le server est allume on accepte de la data ou des nouveaux clients
	while (!Server::_Signal)
	{
		if ((poll(&fds[0], fds.size(), 100) == -1) && Server::_Signal == false)
			throw(std::runtime_error(ERR_POLL_FAIL));
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == SocketFd())
					AcceptNewClient();
				else
					ReceiveNewData(fds[i].fd);
			}
		}
		//! affiche le message toute les x secondes
		if (shouldTriggerEveryXSeconds(1))
			serverMessage();
		
	}
	CloseFds();
}