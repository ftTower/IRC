/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:09:56 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/13 02:35:19 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/commands.hpp"

void	handleCmds(int fd, char buff[1024])
{
	std::string strBuff(buff);
	
	if (strBuff.find("\r\n") == std::string::npos)
		return ;
	size_t pos = 0;
	while ((pos = strBuff.find("\r\n")) != std::string::npos)
	{
		parseCmd(fd, strBuff.substr(0, pos));
		strBuff.erase(0, pos + 2);
	}
}

void	parseCmd(int fd, std::string cmd)
{

	std::cout << YELLOW_BG << BOLD_YELLOW << "Client " << RESET << YELLOW_BG << BOLD_RED << fd << " Data :" << RESET << "\n" << cmd << std::endl; 
	
	std::string cmds[] = {"CAP", "NICK", "USER", "PONG", "PING", "VERSION", "MOTD", "WHOIS", "PASS", "WHO", "JOIN", "PART", "LIST", "PRIVMSG", "INVITE", "QUIT", "MODE", "TOPIC", "NAMES", "KICK"};
	void (*foo[])(int,const std::string &) = {
		cap_cmd, nick_cmd, user_cmd, ping_cmd, pong_cmd, version_cmd, motd_cmd, whois_cmd, pass_cmd, who_cmd, join_cmd, part_cmd, list_cmd, privmsg_cmd, invite_cmd, quit_cmd, mode_cmd, topic_cmd, names_cmd, kick_cmd
	};
	for(size_t i = 0; i < 20; i++)
		if (cmd.find(cmds[i]) != std::string::npos) {
			try {
				foo[i](fd, cmd);}
			catch (std::exception &e) {
				std::cerr << RED_BG << "ERROR CMD [" + cmd + "]" << RESET << " : " << e.what() << std::endl;
			}
			return;
		}
	std::cerr << RED_BG << "found no cmd" << RESET << std::endl;
}