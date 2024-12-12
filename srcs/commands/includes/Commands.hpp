/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:11:32 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/12 11:39:58 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>

void	cap_cmd();
void	nick_cmd();
void	user_cmd();
void	ping_cmd();
void	pong_cmd();
void	version_cmd();
void	motd_cmd();
void	whois_cmd();
void	pass_cmd();
void	who_cmd();
void	join_cmd();
void	part_cmd();
void	list_cmd();
void	privmsg_cmd();
void	invite_cmd();
void	quit_cmd();
void	mode_cmd();
void	topic_cmd();
void	names_cmd();
void	kick_cmd();

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