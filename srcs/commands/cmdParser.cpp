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

	try {
		serv.findClientFd(fd).addCmdToHistoric(cmd);
	
		std::stringstream ss;
		ss << fd;
		std::string buf = getTimestamp() + "\t\t\t" + ss.str() + "\t" + serv.findClientFd(fd).nickName() + "\t";
		for(size_t i = 0; i < commands.size(); i++)
			buf += commands[i] += " ";
		writeToFile("output.csv", buf + "\n");
		
		//if ((commands.size() >= 1 && commands[0] == "CAP") || (commands.size() >= 2 && commands[0] == "CAP" && commands[1] == "LS"))
		//	return ;
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
