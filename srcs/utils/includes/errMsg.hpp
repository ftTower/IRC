/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errMsg.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:59:54 by tauer             #+#    #+#             */
/*   Updated: 2024/12/05 02:32:40 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

//?server
#define ERR_SOCKET	"faild to create a socket"
#define ERR_SOCKET_OPTION_R "faild to set option (SO_REUSEADDR) on socket"
#define ERR_SOCKET_OPTION_N "faild to set option (O_NONBLOCK) on socket"
#define ERR_SOCKET_BIND "faild to bind on socket"
#define ERR_SOCKET_LISTEN "faild to listen on socket"

#define ERR_SOCKET_OPTION_EBADF "The socket argument is not a valid file descriptor."
#define ERR_SOCKET_OPTION_EDOM "The send and receive timeout values are too big to fit into the timeout fields in the socket structure."
#define ERR_SOCKET_OPTION_EINVAL "The specified option is invalid at the specified socket level or the socket has been shut down."
#define ERR_SOCKET_OPTION_EISCONN "The socket is already connected, and a specified option cannot be set while the socket is connected."
#define ERR_SOCKET_OPTION_ENOPROTOOPT "The option is not supported by the protocol."
#define ERR_SOCKET_OPTION_ENOTSOCK "The socket argument does not refer to a socket."
#define ERR_SOCKET_OPTION_ENOMEM "There was insufficient memory available for the operation to complete."
#define ERR_SOCKET_OPTION_ENOBUFS "Insufficient resources are available in the system to complete the call."

#define ERR_POLL_FAIL "Faild to poll"



