
#pragma once

#include "../../client/includes/Client.hpp"
#include <vector>
#include <iostream>
#include <ctime>


class Channel
{
private:
	std::string 		_name;
	std::string 		topic;
	std::string			password;

	std::vector<Client> users;
	std::vector<Client> operators;
	std::vector<Client> invitations;
	
	std::time_t 		creationTime;
	bool 				modes[4];

public:
	//! Base
	Channel(std::string &Name);

	//! getters
	std::string 		getChanName(void);
	std::string 		getTopic(void);
	std::string 		getPassword(void);
	std::vector<Client> getUsersList(void);
	std::vector<Client> getOperatorsList(void);
	std::vector<Client> getInvitationsList(void);
	std::time_t 		getCreationTime(void);
	bool 				*getModes();
	
	//! setters
	void 				setModes(t_mode mode, bool toSet);
	void				setTopic(std::string topic);
	void				setPassword(std::string password);
	void 				addClient(Client &newClient);
	void 				addOperator(Client &newClient);
	void 				addInvitation(Client &newClient);

	//! methods
	bool				isClientConnected(Client &Client);
	bool 				isClientOperator(Client &newOperator);
	bool 				isClientInvited(Client &newOperator);
	void 				kickClient(int fd);
	void 				kickOperator(int fd);
	void 				kickInvitation(int fd);
	

	//~Channel();
};