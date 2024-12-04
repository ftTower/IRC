/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:17:22 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 23:05:42 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/includes/server.hpp"


int	main(int argc, char **argv){
	
	if (argc != 2)
		return (1);
	try {

		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		
		Server S(atoi(argv[1]));

		
	} catch (std::exception &e) {
		std::cerr << RED_BG << "ERROR : " << e.what() << std::endl;
	}
		
	// std::cout << std::endl << argv[0] << " launched on port\t" << S.Port() << 
	// "\n\nsocketFd :\t" << S.SocketFd() << std::endl;
	
	return(0);
}
