/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:53:49 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 01:56:06 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Server.hpp"

void	throwSocketOptionError(int socketOptionRet, std::string optionType)
{
	if (socketOptionRet == -1)
	{
		switch (errno)
		{
		case EBADF:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EBADF);
		case EDOM:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EDOM);
		case EINVAL:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EINVAL);
		case EISCONN:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_EISCONN);
		case ENOPROTOOPT:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOPROTOOPT);
		case ENOTSOCK:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOTSOCK);
		case ENOMEM:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOMEM);
		case ENOBUFS:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + ERR_SOCKET_OPTION_ENOBUFS);
		default:
			throw std::runtime_error(optionType + RESET + BOLD_RED
				+ " " + "Unknown socket option error");
		}
	}
}
