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
	if (argc != 2)
		return (1);
	std::cout << "\033c";
	Server S(atoi(argv[1]));
	try
	{
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		S.Run();
	}
	catch (std::exception &e)
	{
		S.CloseFds();
		std::cerr << RED_BG << BOLD_RED << "ERROR : " << e.what() << std::endl;
	}
	std::cout << std::endl << getTimestamp() << RED_BG << BOLD_RED << "\tSERVER DOWN" << RESET << std::endl;
	return (0);
}
