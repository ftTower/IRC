/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:40:19 by lleciak           #+#    #+#             */
/*   Updated: 2025/01/30 14:53:46 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Commands.hpp"
#include "../channel/includes/Channel.hpp"
#include "./includes/numericReplies.hpp"
#include "../client/includes/Client.hpp"
#include <sstream>

// Parameters: <arg>
// void	cap_cmd(Server &serv, int fd, std::vector<std::string> cmd)
// {
void    capls_cmd(Server &serv, int fd, std::vector<std::string> cmd) {
	(void)serv;
	(void)fd;
	(void)cmd;
}
// }

void handleClientName(Server &serv, Client &client ,std::string nickName) {
	
	nickName.erase(std::remove_if(nickName.begin(), nickName.end(), ::isspace), nickName.end());
	
	while(serv.isNickUsed(nickName, client.Fd()))
		nickName += "_";
	client.setNickname(nickName);
}


// Pour donner au client un nickname ou changer le precedent.
// Parameters: <nickname>
void	nick_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	if (cmd.size() != 2) {
		serv.addError(std::string("Invalid number of parameters for NICK command from ") + serv.findClientFd(fd).nickName());
		throw std::runtime_error("Invalid number of parameters for NICK command");
	}
	std::string nickname = cmd[1];
	Client& client = serv.findClientFd(fd);

	handleClientName(serv, client, nickname);
		
	std::string welcome = ":server 001 " + client.nickName() + " :Welcome to the IRC server\r\n";
	
	if (send(fd, welcome.c_str(), welcome.size(), 0) < 0) {
		serv.addError(std::string("failed to send welcome to ") + client.nickName());
		throw(std::runtime_error(std::string("failed to send welcome to ") + client.nickName()));
	}
}

// On l'utilise au debut de la connexion pour specifier 
// l'username et le realname d'un nouvel utilisateur.

// Parameters: <nickname> <IP Address> <realname>
void	user_cmd(Server &serv, int fd,std::vector<std::string> cmd)//, std::string Ip, std::string realName)
{
	Client& client = serv.findClientFd(fd);
	//std::cout << cmd[0] + '\n' << cmd[1] + '\n' << cmd[2] + '\n' << cmd[3] + '\n' << std::endl;
	
	handleClientName(serv, client, cmd[1]);

	client.setIPadd(cmd[2]);
	client.setRealName(cmd[3]);
}

void	ping_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// Envoye par soit le client soit le serveur pour verifier
	// si l'autre cote de la connexion est toujours connecte

	// Parameters: <token>
}

void	pong_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	
	// Utilise comme une reponse a PING par le client ou le serveur

	// Parameters: [<server>] <token>
	(void)serv;
	(void)cmd;
	const char *Pong = "PONG localhost\n";
	if (send(fd, Pong, strlen(Pong), 0) < 0) {
		serv.addError(std::string("failed to pong ") + serv.findClientFd(fd).nickName());
		throw(std::runtime_error(std::string("failed to pong ") + serv.findClientFd(fd).nickName()));
	}
	serv.findClientFd(fd).setNbPingUp();
}

void	version_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// La commande version permet d'interroger la version du logiciel
	// et les parametres du serveur donne

	// Parameters: [<target>]
}

// Permet de set un mot de passe de connexion
// Parameters: <password>
void	pass_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	Client &client = serv.findClientFd(fd);
	
	if (!serv.getPass()) {
		client.setAuthenticated(true);
		return ; 
	}
	
	cmd[1].erase(std::remove_if(cmd[1].begin(), cmd[1].end(), ::isspace), cmd[1].end());
	
	//! verifie la size de la cmd
    if (cmd.size() < 2) {
		std::string msg = ":myserver 461 " + cmd[0] + " :Not enough parameters\r\n";
		Send(fd, msg);
	}
	//! verfie si le client nest pas deja authentifie
	if (client.getAuthenticated()) {
		std::string msg = ":myserver 462 * :You may not reregister\r\n";
		Send(fd, msg);
		return;
	}
	//! check le password
	if (cmd[1] != serv.getPassword()) {
		std::string msg = ":myserver 464 * :Password incorrect\r\n";
		Send(fd, msg);

		usleep(100000);
		
		shutdown(fd, SHUT_WR);
		serv.kickClient(fd);
		return;
	}
    client.setAuthenticated(true);
}


// Parameters: <channel> <password>
void	join_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	// Channel& chan = serv.getChan(cmd[1]);
	// est-ce que le channel existe ?
	if (cmd.size() < 2) {
		std::string msg = ":myserver 461 " + serv.findClientFd(fd).nickName() + " JOIN :Not enough parameters\r\n";
		Send(fd, msg);
		serv.addError("Not enough parameters for JOIN command from " + serv.findClientFd(fd).nickName());
		throw(std::runtime_error("Not enough parameters for JOIN command from " + serv.findClientFd(fd).nickName()));
	}
	else if (cmd.size() > 2) {
		std::string msg = ":myserver 461 " + serv.findClientFd(fd).nickName() + " JOIN :Too many parameters\r\n";
		Send(fd, msg);
		throw(std::runtime_error("Too many parameters for JOIN command from " + serv.findClientFd(fd).nickName()));
	}
	cmd[1].erase(std::remove_if(cmd[1].begin(), cmd[1].end(), ::isspace), cmd[1].end());
	if (!serv.channelExist(cmd[1])){
		serv.addChannel(Channel(cmd[1]));
	}
	serv.addClientToChannel(fd, cmd[1]);
	serv.findClientFd(fd).addChannelToList(cmd[1]);
	//serv.channelMessage(3, true);
}

void part_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	//! a fix
	
	// Enleve le client d'un channel donne. L'utilisateur 
	// recevra un message du serveur pour chaque channel
	// dont il a ete enleve.

	// Parameters: <channel>{,<channel>} [<reason>]

	if (cmd.size() < 2) {
		serv.addError("Not enough parameters for PART command from " + serv.findClientFd(fd).nickName());
		throw std::runtime_error("Not enough parameters for PART command");
	}

	Client &client = serv.findClientFd(fd);
	std::vector<std::string> channels = splitString(cmd[1], ',');
	std::string reason = cmd.size() > 2 ? cmd[2] : "Left channel";

	for (size_t i = 0; i < channels.size(); ++i) {
		channels[i].erase(std::remove_if(channels[i].begin(), channels[i].end(), ::isspace), channels[i].end());
		
		if (!serv.channelExist(channels[i])) {
			serv.addError("Channel doesn't exist from " + serv.findClientFd(fd).nickName());
			//! Send error that channel doesn't exist
			continue;
		}

		//! Remove client from channel
		for(size_t i = 0; i < channels.size(); i++) {
			serv.getChan(channels[i]).kickClient(fd);
			client.removeChannelToList(channels[i]);
		}

		//! Send part message to channel
		std::string partMsg = ":" + client.nickName() + " PART " + channels[i] + " :" + reason + "\r\n";
		serv.sendMessage(channels, partMsg, client);
	}
}

void privmsg_cmd(Server &serv, int fd, std::vector<std::string> cmd) {
    if (cmd.size() < 3) {
		serv.addError("Not enough parameters for PRIVMSG command from " + serv.findClientFd(fd).nickName());
        throw std::runtime_error("Not enough parameters for PRIVMSG command");
    }

	//! cherche les targets et les format
    Client &sender = serv.findClientFd(fd); 
    std::vector<std::string> targets = splitString(cmd[1], ',');
    for (size_t i = 0; i < targets.size(); ++i) {
        if (targets[i].empty()) {
            std::cerr << "Cible invalide détectée." << std::endl;
            serv.addError("Cible invalide détectée.");
			return;
        }
		targets[i].erase(std::remove_if(targets[i].begin(), targets[i].end(), ::isspace), targets[i].end());
		
    }

	//! cherche le message a transmettre
    std::string message;
    for (size_t i = 2; i < cmd.size(); ++i) {
        message += cmd[i] + " ";
    }
    if (!message.empty() && message[message.size() - 1] == ' ') {
        message.erase(message.end() - 1);
    }

    serv.sendMessage(targets, message, sender);
}

void	invite_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// Commande utilisee pour inviter un utilisateur dans un channel

	// Parameters: <nickname> <channel>
	
}

void	quit_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	std::string reason = cmd.size() > 1 ? cmd[1] : "Client disconnected";
	std::cout << "\t\t\t\t\t\t" << RED_BG << BOLD_RED << "Client " << RESET << RED_BG << BOLD_YELLOW << fd << RESET << RED_BG << " Disconnected: " << reason << RESET << std::endl;
	
	serv.ClearClients(fd);
	shutdown(fd, SHUT_RDWR);
	close(fd);
}

void	mode_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// On l'utilise pour mettre ou enlever des options (ou modes)
	// d'une target donne.

	// Parameters: <target> [<modestring> [<mode arguments>...]]
	if (cmd.size() < 3) {
		serv.addError("Not enough parameters for MODE command from " +  serv.findClientFd(fd).nickName());
		throw std::runtime_error("Not enough parameters for MODE command from " +  serv.findClientFd(fd).nickName());
	}
	
	cmd[1].erase(std::remove_if(cmd[1].begin(), cmd[1].end(), ::isspace), cmd[1].end());
	if (!serv.channelExist(cmd[1])) {
		std::string msg = ":myserver 403 " + serv.findClientFd(fd).nickName() + " " + cmd[1] + " :No such channel\r\n";
		Send(fd, msg);
		throw std::runtime_error("Channel " + cmd[1] + " does not exist.");
	}
	Channel &buf = serv.getChan(cmd[1]);
	
	bool toSet;
	 
	if (cmd[2].empty()) {
		serv.addError("Invalid argument for MODE command from " +  serv.findClientFd(fd).nickName());
		throw std::runtime_error("Invalid argument for MODE command from " +  serv.findClientFd(fd).nickName());
	}
	else if (cmd[2][0] == '+')
		toSet = true;
	else if (cmd[2][0] == '-')
		toSet = false;
	else  {
		serv.addError("Invalid argument for MODE command from " +  serv.findClientFd(fd).nickName());
		throw std::runtime_error("Invalid argument for MODE command from " +  serv.findClientFd(fd).nickName());
	}
		
	for (size_t i = 2; i < cmd.size(); ++i) {
		if (cmd[i].empty() || cmd[i].size() < 2)
			break ;
		else if (cmd[i][1] == 'i') 
			buf.setModes(MODE_INVITE, toSet);
		else if (cmd[i][1] == 't') 
			buf.setModes(MODE_TOPIC, toSet);
		else if (cmd[i][1] == 'k') 
			buf.setModes(MODE_KEY, toSet);
		else if (cmd[i][1] == 'o') 
			buf.setModes(MODE_OP, toSet);
	}
}

// void mode_cmd(Server &serv, int fd, std::vector<std::string> cmd)
// {
// 	if (cmd.size() < 3) {
// 		serv.addError("Not enough parameters for MODE command from " + serv.findClientFd(fd).nickName());
// 		throw std::runtime_error("Not enough parameters for MODE command from " + serv.findClientFd(fd).nickName());
// 	}

// 	// Vérifier si le canal existe
// 	if (!serv.channelExists(cmd[1])) {
// 		serv.addError("Channel " + cmd[1] + " does not exist.");
// 		throw std::runtime_error("Channel " + cmd[1] + " does not exist.");
// 	}

// 	Channel &buf = serv.getChan(cmd[1]);

// 	// Vérifier si l'utilisateur est dans le canal
// 	Client &client = serv.findClientFd(fd);
// 	if (!buf.isClientInChannel(client)) {
// 		serv.addError("User " + client.nickName() + " is not in channel " + cmd[1]);
// 		throw std::runtime_error("User " + client.nickName() + " is not in channel " + cmd[1]);
// 	}

// 	// Vérifier le format du mode (+ ou - en premier caractère)
// 	bool toSet;
// 	if (cmd[2].empty() || (cmd[2][0] != '+' && cmd[2][0] != '-')) {
// 		serv.addError("Invalid mode format from " + client.nickName());
// 		throw std::runtime_error("Invalid mode format from " + client.nickName());
// 	}
// 	toSet = (cmd[2][0] == '+');

// 	// Vérifier si l'utilisateur est opérateur avant de modifier certains modes
// 	if (!buf.isOperator(client)) {
// 		serv.addError("User " + client.nickName() + " is not a channel operator.");
// 		throw std::runtime_error("User " + client.nickName() + " is not a channel operator.");
// 	}

// 	size_t argIndex = 3;
// 	for (size_t i = 1; i < cmd[2].size(); ++i) {
// 		switch (cmd[2][i]) {
// 			case 'i': // Mode invitation-only
// 				buf.setModes(MODE_INVITE, toSet);
// 				break;
// 			case 't': // Mode topic restreint
// 				buf.setModes(MODE_TOPIC, toSet);
// 				break;
// 			case 'k': // Mode mot de passe (nécessite un argument)
// 				if (argIndex >= cmd.size()) {
// 					serv.addError("Missing argument for mode 'k'.");
// 					throw std::runtime_error("Missing argument for mode 'k'.");
// 				}
// 				buf.setKey(toSet ? cmd[argIndex] : "");
// 				argIndex++;
// 				break;
// 			case 'o': // Mode opérateur (nécessite un argument)
// 				if (argIndex >= cmd.size()) {
// 					serv.addError("Missing argument for mode 'o'.");
// 					throw std::runtime_error("Missing argument for mode 'o'.");
// 				}
// 				buf.setOperator(cmd[argIndex], toSet);
// 				argIndex++;
// 				break;
// 			default:
// 				serv.addError("Unknown mode '" + std::string(1, cmd[2][i]) + "' from " + client.nickName());
// 				throw std::runtime_error("Unknown mode '" + std::string(1, cmd[2][i]) + "' from " + client.nickName());
// 		}
// 	}
// }


void	topic_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// On l'utilise pour changer ou voir un topic du channel donne.

	// Parameters: <channel> [<topic>]
}

void	kick_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// Peut etre utilise pour demander de supprimer de force 
	// un utilisateur dans un channel

	// Parameters: <channel> <user> *("," <user>) [<comment>]

	//std::cout << "\t\t\t\t\t\t" << RED_BG << BOLD_RED << "Client " << RESET << RED_BG << BOLD_YELLOW << fd << RESET << RED_BG << " Disconnected !" << RESET << std::endl;
	// serv.ClearClients(fd);
	// close(fd);
}

void    who_cmd(Server &serv, int fd, std::vector<std::string> cmd){
    (void)cmd;
	// The mask can be one of the following:

    // A channel name, in which case the channel members are listed.
    // An exact nickname, in which case a single user is returned.
    // A mask pattern, in which case all visible users whose nickname matches are listed. Servers MAY match other user-specific values, such as the hostname, server, real name or username. Servers MAY not support mask patterns and return an empty list.

    //std::cout << "Dans quel(s) channel(s) est " << serv.findClientFd(fd).nickName() << " ?\n" << std::endl;
	std::cout << getTimestamp() << "\t" << serv.findClientFd(fd).nickName() << " ";
	std::vector<std::string> channelsList = serv.findClientFd(fd).getChannelList();
	for (size_t i = 0; i < channelsList.size(); i++)
		std::cout << channelsList[i] << " ";
	std::cout << "\n";
}

// aligner les :
void    whois_cmd(Server &serv, int fd, std::vector<std::string> cmd){
    if (cmd.size() == 1)
    {
        std::cout << "ircname: " << serv.findClientFd(fd).nickName() << std::endl;
        std::cout << "modes: " << "add modes ? ex: +ixz" << std::endl;
        std::cout << "hostname: " << "88-121-161-222.subs.proxad.ned 88.121.161.222" << std::endl;
        std::cout << "server: notre super server irc trop cool.org" << std::endl;
        std::cout << "idle: " << "0 day 0 hours 0 mins 10secs [signon: Thu Jan 30 13:47:44 2025]" << std::endl;
        std::cout << "End of WHOIS" << std::endl;
    }
    if (cmd.size() == 2)
    {
        std::string name = cmd[1];
        std::cout << "ircname: " << serv.findClientNick(name).nickName() << std::endl;
        std::cout << "modes: " << "add modes ? ex: +ixz" << std::endl;
        std::cout << "hostname: " << "88-121-161-222.subs.proxad.ned 88.121.161.222" << std::endl;
        std::cout << "server: notre super server irc trop cool.org" << std::endl;
        std::cout << "idle: " << "0 day 0 hours 0 mins 10secs [signon: Thu Jan 30 13:47:44 2025]" << std::endl;
        std::cout << "End of WHOIS" << std::endl;
    }
}


std::vector<std::string> splitString(std::string str, char sep){

	std::stringstream split(str);
	std::string segment;
	std::vector<std::string> commands;
	while (std::getline(split, segment, sep)){
		commands.push_back(segment);
	}
	return (commands);
}