/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:11:32 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/16 10:49:28 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>

# include "../../utils/includes/colors.hpp"
# include "../../server/includes/server.hpp"

class Server;

void	nick_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	user_cmd(Server &serv, int fd, std::vector<std::string> cmd);//, std::string Ip, std::string realName);
void	ping_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	pong_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	version_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	pass_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	join_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	part_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	privmsg_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	invite_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	quit_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	mode_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	topic_cmd(Server &serv, int fd, std::vector<std::string> cmd);
void	kick_cmd(Server &serv, int fd, std::vector<std::string> cmd);

void	handleCmds(Server &serv, int fd, char buff[1024]);
void	parseCmd(Server &serv, int fd, std::string cmd);

class UserNotFoundException: public std::exception
{
	public:
		virtual const char* what() const throw() {return ("User not found");}
};

class ChannelNotFoundException: public std::exception
{
	public:
		virtual const char* what() const throw() {return ("Channel not found");}
};

class MissingArgumentsException: public std::exception
{
	public:
		virtual const char* what() const throw() {return ("Missing argument in the command");}
};

#endif