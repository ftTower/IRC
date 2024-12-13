/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:11:32 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/13 02:35:55 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>

# include "../../utils/includes/colors.hpp"
# include "../../server/includes/server.hpp"

void	handleCmds(int fd, char buff[1024]);
void	parseCmd(int fd, std::string cmd); // prends un fd pour send data a user concerne

void	cap_cmd(int fd, const std::string &cmd);
void	nick_cmd(int fd, const std::string &cmd);
void	user_cmd(int fd, const std::string &cmd);
void	ping_cmd(int fd, const std::string &cmd);
void	pong_cmd(int fd, const std::string &cmd);
void	version_cmd(int fd, const std::string &cmd);
void	motd_cmd(int fd, const std::string &cmd);
void	whois_cmd(int fd, const std::string &cmd);
void	pass_cmd(int fd, const std::string &cmd);
void	who_cmd(int fd, const std::string &cmd);
void	join_cmd(int fd, const std::string &cmd);
void	part_cmd(int fd, const std::string &cmd);
void	list_cmd(int fd, const std::string &cmd);
void	privmsg_cmd(int fd, const std::string &cmd);
void	invite_cmd(int fd, const std::string &cmd);
void	quit_cmd(int fd, const std::string &cmd);
void	mode_cmd(int fd, const std::string &cmd);
void	topic_cmd(int fd, const std::string &cmd);
void	names_cmd(int fd, const std::string &cmd);
void	kick_cmd(int fd, const std::string &cmd);

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