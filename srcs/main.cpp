/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:17:22 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 02:04:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/includes/Server.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2 || argc > 3 )
		return (1);

	//! ainsi escape code pour clear le terminal
	std::cout << "\033c";
	
	Server S(argv);
	try
	{
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		//! lancement du serveur
		S.Run();
	}
	catch (std::exception &e)
	{
		S.CloseFds();
		std::cerr << RED_BG << BOLD_RED << "ERROR : " << e.what() << std::endl;
	}
	closingMessage();
	return (0);
}
