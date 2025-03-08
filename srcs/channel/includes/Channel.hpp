
#pragma once

#include "../../client/includes/Client.hpp"
#include <vector>
#include <iostream>
#include <ctime>
typedef enum e_mode {
	MODE_INVITE,
	MODE_TOPIC,
	MODE_KEY,
	MODE_OP,
} t_mode;

class Channel {
	private :
		std::string _name;
		std::string topic;
		
		std::vector <Client> users; // Clients connected to channel
		
		bool modes[4];
		std::time_t creationTime;
	public :
		Channel(std::string &Name);

		std::string	getChanName(void);
		std::string getTopic(void);
		std::vector <Client> getUsersList(void);
		std::time_t getCreationTime(void);
		
		bool* getModes();
		void  addClient(Client &newClient);
		void  kickClient(int fd);

		void	setModes(t_mode mode, bool toSet);
		//~Channel();
};