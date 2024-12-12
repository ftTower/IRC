/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exception.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:11:32 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/12 11:18:17 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXCEPTIONS_HPP
# define CMD_EXCEPTIONS_HPP

# include <iostream>

class UserNotFoundException: public std::exception
{
	public:
		virtual const char* what() const throw() {return ("User not found");}
};

class ChannelNotFoundException: public std::exception
{
	public:
		virtual const char* what() const throw() {return ("Channel not found");}
};


#endif