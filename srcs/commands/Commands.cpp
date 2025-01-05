/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:40:19 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/16 10:49:57 by lleciak          ###   ########.fr       */
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

// }

// Pour donner au client un nickname ou changer le precedent.
// Parameters: <nickname>
void	nick_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	std::string nickname = cmd[1];
	Client& client = serv.findClientFd(fd);
	if (serv.isNickUsed(nickname))
	{
		std::cout << "Nickname unavailable." << std::endl;
		return;
	}
	client.setNickname(nickname);
	/////

	std::string welcome = ":server 001 " + nickname + " :Welcome to the IRC server\r\n";
	
	if (send(fd, welcome.c_str(), welcome.size(), 0) < 0)
		throw(std::runtime_error(std::string("failed to send : ") + nickname));
	
	std::cout << "\t\t\t\t\t\t" << GREEN_BG << BOLD_GREEN << "Client "  << RESET <<  GREEN_BG << BOLD_YELLOW << fd << " " <<  nickname << RESET << GREEN_BG << " Named !" << RESET << std::endl;
}

// On l'utilise au debut de la connexion pour specifier 
// l'username et le realname d'un nouvel utilisateur.

// Parameters: <nickname> <IP Address> <realname>
void	user_cmd(Server &serv, int fd,std::vector<std::string> cmd)//, std::string Ip, std::string realName)
{
	Client& client = serv.findClientFd(fd);
	std::cout << cmd[0] + '\n' << cmd[1] + '\n' << cmd[2] + '\n' << cmd[3] + '\n' << std::endl;
	if (serv.isNickUsed(cmd[1]))
		client.setNickname(cmd[1] + "_");
	else
		client.setNickname(cmd[1]);
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
		
	std::cout << "\t\t\t\t\t\t" << YELLOW_BG << BOLD_YELLOW "PONGED CLIENT " << fd << RESET << std::endl;
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

	// if (cmd[1].empty()){
	// 	ERR_NEEDMOREPARAMS
	// }
	// else if ()
}

// Parameters: <channel> <password>
void	join_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	Channel& chan = serv.getChan(cmd[1]);
	// est-ce que le channel existe ?
	if (serv.channelExist(cmd[1])){
		chan.addClient(serv.findClientFd(fd));
		serv.addChannel(chan);
		return;
	}
	
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

void	privmsg_cmd(Server &serv, int fd, std::vector<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	(void)serv;

	// Pour envoyer des messages prives entre utilisateurs

	// Parameters: <target>{,<target>} <text to be sent>
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

	std::cout << "\t\t\t\t\t\t" << RED_BG << BOLD_RED << "Client " << RESET << RED_BG << BOLD_YELLOW << fd << RESET << RED_BG << " Disconnected !" << RESET << std::endl;
	// Server::ClearClients(fd);
	// close(fd);
}

/////// utils

std::vector<std::string> splitString(std::string str, char sep){

	std::stringstream split(str);
	std::string segment;
	std::vector<std::string> commands;
	while (std::getline(split, segment, sep)){
		commands.push_back(segment);
	}
	return (commands);
}