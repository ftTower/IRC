
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

	std::time_t creationTime;

public:
	//! Base
	Channel(std::string &Name);

	//! getters
	std::string getChanName(void);
	std::string getTopic(void);
	std::vector<Client> getUsersList(void);
	std::time_t getCreationTime(void);

	//! setters

	//! methods
	void addClient(Client &newClient);
	void kickClient(int fd);

	//~Channel();
};