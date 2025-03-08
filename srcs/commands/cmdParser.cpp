/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:09:56 by lleciak           #+#    #+#             */
/*   Updated: 2025/01/30 14:33:01 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Commands.hpp"
#include <sstream>

void	handleCmds(Server &serv, int fd, char buff[1024])
{
	std::string strBuff(buff);
	if (strBuff.find("\r\n") == std::string::npos)
		return ;
	size_t pos = 0;
	while ((pos = strBuff.find("\r\n")) != std::string::npos)
	{
		parseCmd(serv, fd, strBuff.substr(0, pos));
		strBuff.erase(0, pos + 2);
	}
}

void	parseCmd(Server &serv, int fd, std::string cmd)
{
	std::vector<std::string> commands = splitString(cmd, ' ');
	if (commands.empty())
		return ;


	try {
		Client &client = serv.findClientFd(fd);
		client.addCmdToHistoric(cmd);
	
		//! ecrit dans output
		std::stringstream ss;
		ss << fd;
		std::string buf = getTimestamp() + "\t\t\t" + ss.str() + "\t" + client.nickName() + "\t";
		for(size_t i = 0; i < commands.size(); i++)
			buf += commands[i] += " ";
		writeToFile("output.csv", buf + "\n");
		
		
		//! verifie que le client a fourni un mdp valide si il y en a un
		commands[0].erase(std::remove_if(commands[0].begin(), commands[0].end(), ::isspace), commands[0].end());
		std::cout << serv.getPass() << " " << !client.getAuthenticated() << " [" << commands[0] << "]\n";
		if (serv.getPass() && !client.getAuthenticated() && (commands[0] != "PASS" && commands[0] != "CAP")) {
			std::string msg = ":myserver 462 * :You may not reregister 2\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			return;
		}
		
		//! parser de commandes
		std::string cmds[] = {"CAP", "NICK", "USER", "PING", "PONG", "WHO", "WHOIS", "VERSION", "PASS", "JOIN", "PART", "PRIVMSG", "INVITE", "QUIT", "MODE", "TOPIC", "KICK"};
		void (*foo[])(Server&,int,std::vector<std::string>) = {
			capls_cmd ,nick_cmd, user_cmd, pong_cmd, ping_cmd, who_cmd, whois_cmd, version_cmd, pass_cmd, join_cmd, part_cmd, privmsg_cmd, invite_cmd, quit_cmd, mode_cmd, topic_cmd, kick_cmd
		};
		for(size_t i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i++)
			if (cmd.find(cmds[i]) != std::string::npos) {
				try {
					foo[i](serv,fd, commands);}
				catch (std::exception &e) {
					std::cerr << RED_BG << "ERROR CMD [" + cmd + "]" << RESET << " : " << e.what() << std::endl;
				}
				return;
			}
		std::cerr << "\t\t\t" << RED_BG << "found no commands > " << cmd << RESET << std::endl;
	} catch (std::exception &e) {
		std::cerr << RED_BG << "Failed to find client" << RESET << " : " << e.what() << std::endl;
		
	}

	
	
}
