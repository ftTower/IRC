/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:09:56 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/16 08:18:04 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/commands.hpp"

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

	std::cout << YELLOW_BG << BOLD_YELLOW << "Client " << RESET << YELLOW_BG << BOLD_RED << fd << " Data :" << RESET << "\n" << cmd << std::endl; 
	
	std::string cmds[] = {"NICK", "USER", "PING", "PONG", "VERSION", "PASS", "JOIN", "PART", "PRIVMSG", "INVITE", "QUIT", "MODE", "TOPIC", "KICK"};
	void (*foo[])(Server&,int,const std::string &) = {
		nick_cmd, user_cmd, pong_cmd, ping_cmd, version_cmd, pass_cmd, join_cmd, part_cmd, privmsg_cmd, invite_cmd, quit_cmd, mode_cmd, topic_cmd, kick_cmd
	};
	for(size_t i = 0; i < 14; i++)
		if (cmd.find(cmds[i]) != std::string::npos) {
			try {
				foo[i](serv,fd, cmd);}
			catch (std::exception &e) {
				std::cerr << RED_BG << "ERROR CMD [" + cmd + "]" << RESET << " : " << e.what() << std::endl;
			}
			return;
		}
	std::cerr << RED_BG << "found no cmd" << RESET << std::endl;
}