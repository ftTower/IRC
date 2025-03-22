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
	// cmd[0].erase(std::remove_if(cmd[0].begin(), cmd[0].end(), ::isspace), cmd[0].end());
	
	if (nickName.empty()) {
		std::string msg = ":myserver 431 * :No nickname given\r\n";
		Send(client.Fd(), msg);
		throw std::runtime_error("No nickname given");
	}
	if (serv.isNickUsed(nickName, client.Fd())) {
		if (!serv.getErrors().empty() && serv.getErrors().size() > 1 && 
			(serv.getErrors()[serv.getErrors().size() - 2].find("NICK") == std::string::npos || 
			 serv.getErrors()[serv.getErrors().size() - 2].find("USER") == std::string::npos))
			return ;
		// std::string msg = ":myserver 433 * " + nickName + " :Nickname is already in use\r\n";
		// Send(client.Fd(), msg);
		// throw std::runtime_error("Nickname is already in use");
		while(serv.isNickUsed(nickName, 10000))
			nickName += "_";
	}
	// std::string msg = ":myserver 001 " + client.nickName() + " :Nickname successfully set\r\n";
	// Send(client.Fd(), msg);
	client.setNickname(nickName);
}


// Pour donner au client un nickname ou changer le precedent.
// Parameters: <nickname>
void	nick_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	if (cmd.size() != 2) {
		std::string msg = ":myserver 431 " + serv.findClientFd(fd).nickName() + " :No nickname given\r\n";
		Send(fd, msg);
		throw std::runtime_error("Invalid number of parameters for NICK command from " + serv.findClientFd(fd).nickName());
	}
	std::string nickname = cmd[1];
	Client& client = serv.findClientFd(fd);

	handleClientName(serv, client, nickname);
		
	std::string welcome = ":server 001 " + client.nickName() + " :Welcome to the IRC server\r\n";
	
	Send(fd, welcome);
}

// On l'utilise au debut de la connexion pour specifier 
// l'username et le realname d'un nouvel utilisateur.

// Parameters: <nickname> <IP Address> <realname>
void	user_cmd(Server &serv, int fd,std::vector<std::string> cmd)//, std::string Ip, std::string realName)
{
	if (cmd.size() < 4) {
		std::string msg = ":myserver 461 " + serv.findClientFd(fd).nickName() + " USER :Not enough parameters\r\n";
		Send(fd, msg);
		throw std::runtime_error("Not enough parameters for USER command from " + serv.findClientFd(fd).nickName());
	}

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
		Channel chan(cmd[1]);
		chan.addOperator(serv.findClientFd(fd));
		serv.addChannel(chan);
	}
	else if (serv.channelExist(cmd[1]) && serv.getChan(cmd[1]).getModes()[MODE_INVITE]) {
		std::string msg = ":myserver 473 " + serv.findClientFd(fd).nickName() + " " + cmd[1] + " :Cannot join channel (+i)\r\n";
		Send(fd, msg);
		throw(std::runtime_error(":myserver 473 " + serv.findClientFd(fd).nickName() + " " + cmd[1] + " :Cannot join channel (+i)\r\n"));
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
		throw std::runtime_error("Not enough parameters for PART command from " + serv.findClientFd(fd).nickName());
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
	if (cmd.size() < 2) {
		std::string msg = ":myserver 461 " + serv.findClientFd(fd).nickName() + " INVITE :Not enough parameters\r\n";
		Send(fd, msg);
		throw std::runtime_error("Not enough parameters for INVITE command from " + serv.findClientFd(fd).nickName());
	}
	else {
		for (size_t i = 0; i < cmd.size(); i++) {
			cmd[i].erase(std::remove_if(cmd[i].begin(), cmd[i].end(), ::isspace), cmd[i].end());
		}
		
		Client& invited = serv.findClientNick(cmd[1]);
		Channel& chan = serv.getChan(cmd[2]);
		
		chan.addInvitation(invited);
		std::string msg = ":" + serv.findClientFd(fd).nickName() + std::string(" INVITE ") + invited.nickName() + " :" + chan.getChanName() + "\r\n";
		Send(invited.Fd(), msg);
	}
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
		throw std::runtime_error("Not enough parameters for MODE command from " +  serv.findClientFd(fd).nickName());
	}
	cmd[1].erase(std::remove_if(cmd[1].begin(), cmd[1].end(), ::isspace), cmd[1].end());
	
	if (!serv.channelExist(cmd[1])) {
		std::vector<std::string> historic = serv.findClientFd(fd).getHistoric();
		if (historic.size() > 1) {
			for (size_t i = 1; i < historic.size(); i++) {
				if (historic[i].find("MODE") != std::string::npos && (historic[i - 1].find("NICK") != std::string::npos || historic[i - 1].find("USER") != std::string::npos)) 
					return ;
		}
	}
		std::string msg = ":myserver 403 " + serv.findClientFd(fd).nickName() + " " + cmd[1] + " :No such channel\r\n";
		Send(fd, msg);
		throw std::runtime_error("Channel " + cmd[1] + " does not exist.");
	}
	Channel &buf = serv.getChan(cmd[1]);
	
	bool toSet;
	
	if (!buf.isClientOperator(serv.findClientFd(fd))) {
		std::string msg = ":myserver 482 " + serv.findClientFd(fd).nickName() + " " + cmd[1] + " :You're not a channel operator\r\n";
		Send(fd, msg);
		throw std::runtime_error("User " + serv.findClientFd(fd).nickName() + " is not a channel operator.");
	}
	else if (cmd[2].empty()) {
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

void	topic_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	// On l'utilise pour changer ou voir un topic du channel donne.

	// Parameters: <channel> [<topic>]

	if (cmd.size() < 2) {
		std::string msg = ":myserver 461 " + serv.findClientFd(fd).nickName() + " TOPIC :Not enough parameters\r\n";
		Send(fd, msg);
		throw std::runtime_error("Not enough parameters for TOPIC command from " + serv.findClientFd(fd).nickName());
	}

	cmd[1].erase(std::remove_if(cmd[1].begin(), cmd[1].end(), ::isspace), cmd[1].end());
	Channel &Chan = serv.getChan(cmd[1]);
	
	if (cmd.size() == 2) {
		if (Chan.getTopic().empty()) {
			std::string msg = ":myserver 331 " + serv.findClientFd(fd).nickName() + " " + Chan.getChanName() + " :No topic is set\r\n";
			Send(fd, msg);
		} else {
			std::string msg = ":myserver 332 " + serv.findClientFd(fd).nickName() + " " + Chan.getChanName() + " :" + Chan.getTopic() + "\r\n";
			Send(fd, msg);
		}
	}
	else {
		if (!Chan.isClientOperator(serv.findClientFd(fd)) && Chan.getModes()[MODE_TOPIC]) {
			std::string msg = ":myserver 482 " + serv.findClientFd(fd).nickName() + " " + Chan.getChanName() + " :You're not a channel operator\r\n";
			Send(fd, msg);
			throw std::runtime_error("User " + serv.findClientFd(fd).nickName() + " is not a channel operator.");
		}
		Chan.setTopic(cmd[2]);
		std::string msg = ":myserver 332 " + serv.findClientFd(fd).nickName() + " " + Chan.getChanName() + " :" + cmd[2] + "\r\n";
		Send(fd, msg);
	}
}

void	kick_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	if (cmd.size() < 3) {
		std::string msg = ":myserver 461 " + serv.findClientFd(fd).nickName() + " KICK :Not enough parameters\r\n";
		Send(fd, msg);
		throw std::runtime_error("Not enough parameters for KICK command from " + serv.findClientFd(fd).nickName());
	}

	std::string channelName = cmd[1];
	std::vector<std::string> users = splitString(cmd[2], ',');
	std::string comment = cmd.size() > 3 ? cmd[3] : "Kicked";

	channelName.erase(std::remove_if(channelName.begin(), channelName.end(), ::isspace), channelName.end());

	if (!serv.channelExist(channelName)) {
		std::string msg = ":myserver 403 " + serv.findClientFd(fd).nickName() + " " + channelName + " :No such channel\r\n";
		Send(fd, msg);
		throw std::runtime_error("Channel " + channelName + " does not exist.");
	}

	Channel &channel = serv.getChan(channelName);

	if (!channel.isClientOperator(serv.findClientFd(fd))) {
		std::string msg = ":myserver 482 " + serv.findClientFd(fd).nickName() + " " + channelName + " :You're not a channel operator\r\n";
		Send(fd, msg);
		throw std::runtime_error("User " + serv.findClientFd(fd).nickName() + " is not a channel operator.");
	}

	for (size_t i = 0; i < users.size(); ++i) {
		users[i].erase(std::remove_if(users[i].begin(), users[i].end(), ::isspace), users[i].end());

		if (!channel.isClientConnected(serv.findClientNick(users[i]))) {
			std::string msg = ":myserver 441 " + serv.findClientFd(fd).nickName() + " " + users[i] + " " + channelName + " :They aren't on that channel\r\n";
			Send(fd, msg);
			continue;
		}

		Client &client = serv.findClientNick(users[i]);
		std::vector<std::string> vec;
		vec.push_back(client.nickName());
		channel.kickClient(client.Fd());
		client.removeChannelToList(channelName);

		std::string kickMsg = ":" + serv.findClientFd(fd).nickName() + " KICK " + channelName + " " + client.nickName() + " :" + comment + "\r\n";
		serv.sendMessage(vec, kickMsg, serv.findClientFd(fd));
	}
}

void    who_cmd(Server &serv, int fd, std::vector<std::string> cmd){
	if (cmd.size() < 2) {
		std::string msg = ":myserver 461 " + serv.findClientFd(fd).nickName() + " WHO :Not enough parameters\r\n";
		Send(fd, msg);
		throw std::runtime_error("Not enough parameters for WHO command from " + serv.findClientFd(fd).nickName());
	}

	std::string mask = cmd[1];
	std::vector<std::string> response;

	if (serv.channelExist(mask)) {
		Channel &channel = serv.getChan(mask);
		std::vector<Client> clients = channel.getUsersList();
		for (size_t i = 0; i < clients.size(); ++i) {
			response.push_back(clients[i].nickName());
		}
	} else if (serv.isNickUsed(mask, 10000)) {
		response.push_back(serv.findClientNick(mask).nickName());
	} else {
		std::vector<Client> clients = serv.getAllClients();
		for (size_t i = 0; i < clients.size(); ++i) {
			response.push_back(clients[i].nickName());
		}
	}

	if (response.empty()) {
		std::string msg = ":myserver 315 " + serv.findClientFd(fd).nickName() + " " + mask + " :End of WHO list\r\n";
		Send(fd, msg);
		return;
	}

	for (size_t i = 0; i < response.size(); ++i) {
		std::string msg = ":myserver 352 " + serv.findClientFd(fd).nickName() + " " + response[i] + "\r\n";
		Send(fd, msg);
	}

	std::string endMsg = ":myserver 315 " + serv.findClientFd(fd).nickName() + " " + mask + " :End of WHO list\r\n";
	Send(fd, endMsg);
	
}

// aligner les :
void    whois_cmd(Server &serv, int fd, std::vector<std::string> cmd){
	if (cmd.size() < 2) {
		std::string msg = ":myserver 461 " + serv.findClientFd(fd).nickName() + " WHOIS :Not enough parameters\r\n";
		Send(fd, msg);
		throw std::runtime_error("Not enough parameters for WHOIS command from " + serv.findClientFd(fd).nickName());
	}

	std::string targetNick = cmd[1];
	targetNick.erase(std::remove_if(targetNick.begin(), targetNick.end(), ::isspace), targetNick.end());
	
	if (!serv.isNickUsed(targetNick, 10000)) {
		std::string msg = ":myserver 401 " + serv.findClientFd(fd).nickName() + " " + targetNick + " :No such nick/channel\r\n";
		Send(fd, msg);
		throw std::runtime_error("No such nick/channel");
	}

	Client &target = serv.findClientNick(targetNick);
	std::string msg;

	msg = ":myserver 311 " + serv.findClientFd(fd).nickName() + " " + target.nickName() + " " + target.nickName() + " " + target.realName() + " * :" + target.realName() + "\r\n";
	Send(fd, msg);

	msg = ":myserver 312 " + serv.findClientFd(fd).nickName() + " " + target.nickName() + " myserver :Our super cool IRC server\r\n";
	Send(fd, msg);

	//msg = ":myserver 317 " + serv.findClientFd(fd).nickName() + " " + target.nickName() + " " + std::to_string(target.idleTime()) + " :seconds idle\r\n";
	//Send(fd, msg);

	msg = ":myserver 318 " + serv.findClientFd(fd).nickName() + " " + target.nickName() + " :End of WHOIS list\r\n";
	Send(fd, msg);
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