
#pragma once

#include "../../client/includes/client.hpp"
#include <vector>

typedef enum e_mode {
	MODE_I,
	MODE_T,
	MODE_K,
	MODE_O,
} t_mode;

class Channel {
	private :
		std::string _name();
		std::vector <Client> users; // Clients connected to channel
		
		std::vector <bool> modes;
		
	public :
		Channel(std::string &Name);
		//~Channel();
	
	
};