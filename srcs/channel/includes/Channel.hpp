
#pragma once

#include "../../client/includes/Client.hpp"
#include <vector>

typedef enum e_mode {
	MODE_INVITE,
	MODE_TOPIC,
	MODE_KEY,
	MODE_OP,
} t_mode;

class Channel {
	private :
		std::string _name;
		std::vector <Client> users; // Clients connected to channel
		
		bool modes[4];
		
	public :
		Channel(std::string &Name);
		std::string	getChanName(void);
		void addClient(Client &newClient);
		//~Channel();
	
	
};