/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:25 by tauer             #+#    #+#             */
/*   Updated: 2024/12/16 09:04:34 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utils/includes/colors.hpp"
#include "../../utils/includes/errMsg.hpp"

#include "../../client/includes/Client.hpp"
#include "../../channel/includes/Channel.hpp"
#include "../../commands/includes/Commands.hpp"

#include <iostream>
#include <algorithm>

#include <vector>

#include <errno.h>
#include <stdexcept>
#include <cstring>
#include <string.h>

#include <stdlib.h>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include <csignal>

class Server
{

private:
	int _Port;
	int _SocketFd;

	bool _pass;
	std::string _password;

	static bool _Signal;

	std::vector<Client> clients;
	std::vector<Channel> channels;
	std::vector<std::string> errors;

	std::vector<struct pollfd> fds;

public:
	//! CONSTRUCTOR
	Server(char **argv);

	//! GETTERS
	int Port() const;
	int SocketFd() const;
	std::vector<Channel> getChannelList();
	std::string getPassword() const;
	bool getPass() const;

	//! METHODS
	void Init();
	void Run();

	//! CLIENTS
	void AcceptNewClient();
	void kickClient(int fd);
	void PongClient(int fd);
	void addClientToChannel(int fd, std::string channel);

	//! MESSAGES
	void initMessage();
	void connectedMessage(int incomingFd);
	void disconnectedMessage(int fd);

	//! ROUTINE MESSAGES
	void usersMessage(size_t size, bool displayTime);
	void channelMessage(size_t size, bool displayTime);
	void errorMessage(size_t size);
	void serverMessage();

	//! SERVER HANDLER
	void ReceiveNewData(int fd);
	void HandleNewData(int fd, std::string &Data);
	void HandleNick(int fd, const std::string &Data);

	void sendMessage(std::vector<std::string> &target, const std::string &msg, const Client &sender);

	//! SIGNAL
	static void SignalHandler(int signum);

	//! CLEANING
	void CloseFds();
	void ClearClients(int fd);

	//! COMMANDS UTILS
	Client &findClientFd(int fd);
	Client &findClientNick(std::string nick);
	bool isNickUsed(std::string name, int fd);
	bool channelExist(std::string name);
	Channel &getChan(std::string name);
	void addChannel(Channel chan);
	void addError(std::string error);
};


void writeToFile(const std::string &filename, const std::string &content);
void throwSocketOptionError(int socketOptionRet, std::string optionType);

std::string getTimestamp();
bool shouldTriggerEveryXSeconds(int x);

void closingMessage();