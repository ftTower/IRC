/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:09:56 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/12 11:40:32 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	parse_cmd(std::string cmd)
{
	try
	{
		if (cmd == "CAP")
			cap_cmd();
		else if (cmd == "NICK")
			nick_cmd();
		else if (cmd == "USER")
			user_cmd();
		else if (cmd == "PING")
			ping_cmd();
		else if (cmd == "PONG")
			pong_cmd();
		else if (cmd == "VERSION")
			version_cmd();
		else if (cmd == "MOTD")
			mode_cmd();
		else if (cmd == "WHOIS")
			whois_cmd();
		else if (cmd == "PASS")
			pass_cmd();
		else if (cmd == "WHO")
			who_cmd();
		else if (cmd == "JOIN")
			join_cmd();
		else if (cmd == "PART")
			part_cmd();
		else if (cmd == "LIST")
			list_cmd();
		else if (cmd == "PRIVMSG")
			privmsg_cmd();
		else if (cmd == "INVITE")
			invite_cmd();
		else if (cmd == "QUIT")
			quit_cmd();
		else if (cmd == "MODE")
			mode_cmd();
		else if (cmd == "TOPIC")
			topic_cmd();
		else if (cmd == "NAMES")
			names_cmd();
		else if (cmd == "KICK")
			kick_cmd();
	}
	catch (const UserNotFoundException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const ChannelNotFoundException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const MissingArgumentsException& e)
	{
		std::cerr<< e.what() << std::endl;
	}
}