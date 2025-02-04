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
	if (cmd.size() < 2) {
		throw std::runtime_error("Not enough parameters for NICK command");
	}
	std::string nickname = cmd[1];
	Client& client = serv.findClientFd(fd);

	handleClientName(serv, client, nickname);
	
	std::cout << "[" << client.nickName() << "]\n"; 
	
	std::string welcome = ":server 001 " + client.nickName() + " :Welcome to the IRC server\r\n";
	
	if (send(fd, welcome.c_str(), welcome.size(), 0) < 0)
		throw(std::runtime_error(std::string("failed to send : ") + client.nickName()));
	
	serv.nickMessage(fd, client);
	//serv.usersMessage(3, true);
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

	const char *Pong = "PONG localhost\n";
	if (send(fd, Pong, strlen(Pong), 0) < 0)
		throw(std::runtime_error(std::string("failed to send : ") + cmd[0]));
	serv.pongMessage(fd);
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
	(void) serv;
	(void) fd;
	(void) cmd;
	// Client& client = serv.findClientFd(fd);
	std::cout << "PASS CMD\n";
	// if (cmd[1].empty()){
	// 	ERR_NEEDMOREPARAMS
	// }
	// else if ()
}

// Parameters: <channel> <password>
void	join_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	// Channel& chan = serv.getChan(cmd[1]);
	// est-ce que le channel existe ?
	if (cmd.size() < 2)
		throw(std::runtime_error("Not enough parameters for JOIN command"));
	cmd[1].erase(std::remove_if(cmd[1].begin(), cmd[1].end(), ::isspace), cmd[1].end());
	if (!serv.channelExist(cmd[1])){
		serv.addChannel(Channel(cmd[1]));
	}
	serv.addClientToChannel(fd, cmd[1]);
	serv.findClientFd(fd).addChannelToList(cmd[1]);
	//serv.channelMessage(3, true);
}

void	part_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// Enleve le client d'un channel donne. L'utilisateur 
	// recevra un message du serveur pour chaque channel
	// dont il a ete enleve.

	// Parameters: <channel>{,<channel>} [<reason>]
}

void privmsg_cmd(Server &serv, int fd, std::vector<std::string> cmd) {
    if (cmd.size() < 3) {
        throw std::runtime_error("Not enough parameters for PRIVMSG command");
    }

    Client &sender = serv.findClientFd(fd); 

    std::vector<std::string> targets = splitString(cmd[1], ',');
    for (size_t i = 0; i < targets.size(); ++i) {
        if (targets[i].empty()) {
            std::cerr << "Cible invalide détectée." << std::endl;
            return;
        }
		//else if (serv.findClientNick(targets[i]))
		targets[i].erase(std::remove_if(targets[i].begin(), targets[i].end(), ::isspace), targets[i].end());
		
    }

    std::string message;
    for (size_t i = 2; i < cmd.size(); ++i) {
        message += cmd[i] + " ";
    }

    if (!message.empty() && message[message.size() - 1] == ' ') {
        message.erase(message.end() - 1);
    }

    for (size_t i = 0; i < targets.size(); i++)
        std::cout << GREEN_BG << "Target: " << targets[i] << RESET;
    std::cout << RED_BG << "Message: " << message << RESET << "\n";

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
	(void)fd;
	(void)cmd;
	(void)serv;

	// Commande utilise pour mettre fin a la connexion du client
	// sur le serveur

	// Parameters: [<reason>]
}

void	mode_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// On l'utilise pour mettre ou enlever des options (ou modes)
	// d'une target donne.

	// Parameters: <target> [<modestring> [<mode arguments>...]]
	//if (cmd.size() < 3) {
	//	throw std::runtime_error("Not enough parameters for MODE command");
	//}
	
	//Channel buf = serv.getChan(cmd[1]);
	
	//bool toSet;
	 
	//if (cmd[2].empty())
	//	throw std::runtime_error("Invalid argument for MODE command");
	//else if (cmd[2][0] == '+')
	//	toSet = true;
	//else if (cmd[2][0] == '-')
	//	toSet = false;
	//else 
	//	throw std::runtime_error("Invalid argument for MODE command");
		
	//for (size_t i = 2; i < cmd.size(); ++i) {
	//	if (cmd[i].empty() || cmd[i].size() < 2)
	//		break ;
	//	else if (cmd[i][1] == 'I') 
	//		buf.setModes(MODE_INVITE, toSet);
	//	else if (cmd[i][1] == 'T') 
	//		buf.setModes(MODE_TOPIC, toSet);
	//	else if (cmd[i][1] == 'K') 
	//		buf.setModes(MODE_KEY, toSet);
	//	else if (cmd[i][1] == 'O') 
	//		buf.setModes(MODE_OP, toSet);
	//}
}

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