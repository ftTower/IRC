/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:09:56 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/16 10:49:18 by lleciak          ###   ########.fr       */
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
	
	serv.cmdParseMessage(fd, serv, commands);

	if (cmd == "CAP" || cmd == "LS" || cmd == "CAP LS")
		return ;
	std::string cmds[] = {"NICK", "USER", "PING", "PONG", "VERSION", "PASS", "JOIN", "PART", "PRIVMSG", "INVITE", "QUIT", "MODE", "TOPIC", "KICK"};
	void (*foo[])(Server&,int,std::vector<std::string>) = {
		nick_cmd, user_cmd, pong_cmd, ping_cmd, version_cmd, pass_cmd, join_cmd, part_cmd, privmsg_cmd, invite_cmd, quit_cmd, mode_cmd, topic_cmd, kick_cmd
	};
	for(size_t i = 0; i < 14; i++)
		if (cmd.find(cmds[i]) != std::string::npos) {
			try {
				foo[i](serv,fd, commands);}
			catch (std::exception &e) {
				std::cerr << RED_BG << "ERROR CMD [" + cmd + "]" << RESET << " : " << e.what() << std::endl;
			}
			return;
		}
	std::cerr << RED_BG << "found no cmd" << RESET << std::endl;
}
