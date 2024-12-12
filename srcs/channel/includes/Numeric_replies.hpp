/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Numeric_replies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:02:30 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/12 09:30:05 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

	La plupart des message envoyes d'un client a un serveur generent une
	reponse. La forme de reponse la plus courante est la numeric replies.
	Utilise a la fois pour les erreurs et les reponses normales.
	Contrairement a un message normal, une NR doit contenir une <source>
	et utiliser un nombre a trois chiffres comme commande (les defines ci-dessous).
	Une numeric replies ne peut pas provenir d'un client.
	Une numeric replies est comme un message normal.

*/

#ifndef NUMERIC_REPLIES_HPP
# define NUMERIC_REPLIES_HPP

# define RPL_ISUPPORT 005
# define RPL_AWAY 301
# define RPL_ENDOFWHO 315
# define RPL_ENDOFWHOIS 318
# define RPL_LISTSTART 321
# define RPL_LIST 322
# define RPL_LISTEND 323
# define RPL_NOTOPC 331
# define RPL_TOPIC 332
# define RPL_TOPICWHOTIME 333
# define RPL_INVITING 341
# define RPL_VERSION 351
# define RPL_WHOREPLY 352
# define RPL_NAMREPLY 353
# define RPL_ENDOFNAMES 366
# define RPL_MOTD 372
# define RPL_MOTDSTART 375
# define RPL_ENDOFMOTD 376

# define ERR_NOSUCHNICK 401
# define ERR_NOSUCHSERVER 402
# define ERR_NOSUCHCHANNEL 403
# define ERR_CANNOTSENDTOCHAN 404
# define ERR_TOOMANYCHANNELS 405
# define ERR_TOOMANYTARGET 407
# define ERR_NOORIGIN 409
# define ERR_NORECIPIENT 411
# define ERR_NOTEXTTOSEND 412
# define ERR_NOTOPLEVEL 413
# define ERR_WILDTOPEVEL 414
# define ERR_NOMOTD 422
# define ERR_NONICKNAMEGIVEN 431
# define ERR_ERRONEUSNICKNAME 432
# define ERR_NICKNAMEINUSE 433
# define ERR_NICKCOLLISION 436
# define ERR_USERNOTINCHANNEL 441
# define ERR_NOTONCHANNEL 442
# define ERR_USERONCHANNEL 443
# define ERR_NEEDMOREPARAMS 461
# define ERR_ALREADYREGISTERED 462
# define ERR_PASSWDMISMATCH 464
# define ERR_CHANNELISFULL 471
# define ERR_INVITEONLYCHAN 473
# define ERR_BANNEDFROMCHAN 474
# define ERR_BADCHANNELKEY 475
# define ERR_BADCHANMASK 476
# define ERR_CHANOPRIVSNEEDED 482

#endif