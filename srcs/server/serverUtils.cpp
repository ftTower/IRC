/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:53:49 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 01:56:06 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Server.hpp"

// envoyer un message a un vecteur de target
void Server::sendMessage(std::vector<std::string> &target, const std::string &msg, const Client &sender) {
    std::vector<Client> sendList;

    for (size_t i = 0; i < target.size(); i++) {
        if (!this->channels.empty() && this->channelExist(target[i])) {
            std::vector<Client> buf = this->getChan(target[i]).getUsersList();
            sendList.insert(sendList.end(), buf.begin(), buf.end());
        } else {
            try {
				if (target[i][0] == '"')
					target[i] = target[i].substr(1); // Retirer le '#' pour les canaux privés
				sendList.push_back(this->findClientNick(target[i]));	
			} catch (std::exception &e) {
				std::cerr << "FAILED TO FIND CLIENT NAMED :" << e.what() << std::endl;
			}
        }
    }

    // Construire le message formaté
    std::string formattedMsg = ":" + sender.nickName() + "!" + sender.nickName() + "@localhost PRIVMSG ";
	formattedMsg += target[0] + " :" + msg + "\r\n";

    // Envoyer le message à tous les destinataires
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

//? a gerer plus tard - tower
void	throwSocketOptionError(int socketOptionRet, std::string optionType)
{
	if (socketOptionRet == -1)
	{
		switch (errno)
		{
		case EBADF:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EBADF);
		case EDOM:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EDOM);
		case EINVAL:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EINVAL);
		case EISCONN:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EISCONN);
		case ENOPROTOOPT:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOPROTOOPT);
		case ENOTSOCK:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOTSOCK);
		case ENOMEM:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOMEM);
		case ENOBUFS:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOBUFS);
		default:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + "Unknown socket option error");
		}
	}
}

//! signal
void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << "\033[2K\033[0G";
	Server::_Signal = true;
}

//?cleaning
void Server::CloseFds()
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		disconnectedMessage(clients[i].Fd());
		if (clients[i].Fd() >= 0)
			close(clients[i].Fd());
	}
}

//! time
#include <iostream>
#include <ctime>

std::string getTimestamp() {
    std::time_t now = std::time(0);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "[%H:%M:%S]", std::localtime(&now));
    return std::string(buffer);
}
