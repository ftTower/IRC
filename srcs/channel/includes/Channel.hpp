
#pragma once

#include "../../client/includes/Client.hpp"
#include <vector>
#include <iostream>
#include <ctime>


class Channel
{
private:
	std::string _name;
	std::string topic;

	std::vector<Client> users;
	std::vector<Client> operators;

	std::time_t creationTime;
	bool modes[4];

public:
	//! Base
	Channel(std::string &Name);

	//! getters
	std::string getChanName(void);
	std::string getTopic(void);
	std::vector<Client> getUsersList(void);
	std::vector<Client> getOperatorsList(void);
	std::time_t getCreationTime(void);
	bool 		*getModes();
	
	//! setters
	void setModes(t_mode mode, bool toSet);
	void addClient(Client &newClient);
	void addOperator(Client &newClient);

	//! methods
	bool isClientOperator(Client &newOperator);
	void kickClient(int fd);
	void kickOperator(int fd);
	

	//~Channel();
};