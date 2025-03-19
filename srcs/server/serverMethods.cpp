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

void Server::sendMessage(std::vector<std::string> &targets, const std::string &msg,  Client &sender) {
    if (targets.empty()) {
        return;  //! Aucune cible, rien à faire.
    }

    std::vector<Client> sendList;

    //! Parcours des cibles et traitement de chaque cible
    for (size_t i = 0; i < targets.size(); ++i) {
        std::string trimmedTarget = targets[i];
        trimmedTarget.erase(std::remove_if(trimmedTarget.begin(), trimmedTarget.end(), ::isspace), trimmedTarget.end()); // Enlever les espaces superflus

        //! Vérifier si c'est un canal
        if (trimmedTarget[0] == '#' && this->channelExist(trimmedTarget)) {
            //! Si c'est un canal, ajouter tous les utilisateurs de ce canal à la sendList


			//! permet dajouter lutilisateur apres avoir envoye un message dans un chan dont il ne fait pas parti
			// for (size_t i = 0; i <= getChan(trimmedTarget).getUsersList().size(); i++) {
			// 	if (getChan(trimmedTarget).getUsersList()[i].Fd() == sender.Fd())
			// 		break ;
			// 	else if (i == getChan(trimmedTarget).getUsersList().size()) {
			// 		getChan(trimmedTarget).addClient(sender);
			// 		break;
			// 	}
			// }

            std::vector<Client> channelUsers = this->getChan(trimmedTarget).getUsersList();
            sendList.insert(sendList.end(), channelUsers.begin(), channelUsers.end());
        } else {
            //! Sinon, essayer de trouver le client avec ce pseudo
            try {
                sendList.push_back(this->findClientNick(trimmedTarget));
            } catch (std::exception &e) {
                //! En cas d'erreur (client introuvable), envoyer un numeric reply 401
                std::string errorMsg = "No such nick/channel: " + trimmedTarget;
                std::string numericReply = ":" + std::string("localhost") + " 401 " + sender.nickName() + " " + trimmedTarget + " :" + errorMsg + "\r\n";
                send(sender.Fd(), numericReply.c_str(), numericReply.size(), 0);  // Envoie de la numeric reply au client
                std::cerr << "\t\t" << RED_BG << sender.nickName() << " tried to send to a non-existent user or channel: [" << trimmedTarget << "]" << RESET << std::endl;
            }
        }
    }

    //! Construire le message formaté
    std::string formattedMsg = ":" + sender.nickName() + "!" + sender.nickName() + "@localhost PRIVMSG ";
    formattedMsg += targets[0] + " :" + msg + "\r\n";  // On envoie à la première cible dans le message

    //! Envoi du message à chaque client dans la sendList
    for (size_t i = 0; i < sendList.size(); ++i) {
        if (sendList[i] != sender) {  //! Ne pas envoyer à l'expéditeur
            ssize_t bytesSent = send(sendList[i].Fd(), formattedMsg.c_str(), formattedMsg.size(), 0);
            if (bytesSent < 0) {
                std::cerr << sender.nickName() + " failed to send message to client " + sendList[i].nickName() << "\n";
                addError(sender.nickName() + " failed to send message to client " + sendList[i].nickName());
                kickClient(sendList[i].Fd());  //! Optionnel gérer un échec d'envoi (ici kick le client)
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
		if ((poll(&fds[0], fds.size(), 100) == -1) && Server::_Signal == false) {
			throw(std::runtime_error(ERR_POLL_FAIL));
		}
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