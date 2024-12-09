/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:22:35 by tauer             #+#    #+#             */
/*   Updated: 2024/12/04 03:26:11 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utils/includes/colors.hpp"

#include <iostream>

class Client
{
  private:
	std::string _nickName;
  
	int 		_fd;
	std::string _IPadd;
	
	//std::vector<std::string> channelsList;

  public:
	//!Base
	Client();
	~Client();

	//? setters
	void 		setFd(const int fd);
	void 		setIPadd(const std::string &IPadd);

	//? getters
	int 		Fd() const;
	std::string IPadd() const;
	std::string nickName() const;
};