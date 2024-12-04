/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:17:22 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 01:58:21 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/includes/server.hpp"
#include "client/includes/client.hpp"


int	main(int argc, char **argv){
	
	if (argc != 2)
		return (1);

	Server S(atoi(argv[1]));
		
	std::cout << argv[0] << " launched on port " << S.Port() << std::endl;

	return(0);
}
