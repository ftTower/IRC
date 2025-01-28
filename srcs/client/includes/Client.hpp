/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:35 by tauer             #+#    #+#             */
/*   Updated: 2024/12/16 09:19:17 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utils/includes/colors.hpp"
#include <ctime>
#include <iostream>
#include <vector>

class Client
{
  private:
	std::string _nickName;
	std::string _realName;
  
	int 		_fd;
	int			_serverSock;
	std::string _IPadd;
	
	///? infos sur le clients
	unsigned long nbPing;
	std::time_t connect_time;
	std::vector<std::string> historic;
	//std::vector<std::string> channelsList;

  public:
	//!Base
	Client(int serverSock);
	~Client();

	bool operator!=(const Client &other) const;
	

	//? setters
	void 		setFd(const int fd);
	void 		setIPadd(const std::string &IPadd);
	void		setNickname(std::string name);
	void		setRealName(std::string name);
	void		setNbPingUp();
	void		addCmdToHistoric(std::string &cmd);

	//? getters
	int 		Fd() const;
	int			ServerSock() const;
	std::string IPadd() const;
	std::string nickName() const;
	std::string realName() const;
	size_t  	getNbPing() const;
	std::time_t getConnectTime() const;
	std::vector<std::string> getHistoric() const;

	// listen
	void	ReceiveMessage();

};