/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:40:19 by lleciak           #+#    #+#             */
/*   Updated: 2024/12/12 10:21:12 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Numeric_Replies.hpp"

void	cap_cmd()
{
	// On l'utilise pour la negociation de capacite
	// entre un serveur et un client.

	// Parameters: <subcommand> [:<capabilities>]
}

void	nick_cmd()
{
	// Pour donner au client un nickname ou changer le precedent.

	// Parameters: <nickname>
}

void	user_cmd()
{
	// On l'utilise au debut de la connexion pour specifier 
	// l'username et le realname d'un nouvel utilisateur.

	// Parameters: <username> 0 * <realname>
}

void	ping_cmd()
{
	// Envoye par soit le client soit le serveur pour verifier
	// si l'autre cote de la connexion est toujours connecte

	// Parameters: <token>
}

void	pong_cmd()
{
	// Utilise comme une reponse a PING par le client ou le serveur

	// Parameters: [<server>] <token>
}

void	version_cmd()
{
	// La commande version permet d'interroger la version du logiciel
	// et les parametres du serveur donne

	// Parameters: [<target>]
}

void	motd_cmd()
{
	// MOTD = "Message Of The Day", recuperer le message of the day 
	// d'un serveur donne. Si pas de serveur precise alors
	// il affichera celui du serveur sur lequel est le client.

	// Parameters: [<target>]
}

void	whois_cmd()
{
	// Utilise pour recuperer des informations a propos de l'utilisateur

	// Parameters: [<target>] <nick>
}

void	pass_cmd()
{
	// Permet de set un mot de passe de connexion

	// Parameters: <password>
}

void	who_cmd()
{
	// On l'utilise pour faire une requete d'une liste d'utilisateur
	// qui correspondent au mask donne

	// Parameters: <mask>
}

void	join_cmd()
{
	// Indique que le client veut rejoindre le channel donne.
	// Le serveur qui recupere la commande verifie si le client 
	// peut ou non rejoindre le channel.

	// Parameters: <channel>{,<channel>} [<key>{,<key>}]
}

void	part_cmd()
{
	// Enleve le client d'un channel donne. L'utilisateur 
	// recevra un message du serveur pour chaque channel
	// dont il a ete enleve.

	// Parameters: <channel>{,<channel>} [<reason>]
}

void	list_cmd()
{
	// On l'utilise pour avoir une liste de channel et quelques informations
	// a propos de chaque channel.

	// Parameters: [<channel>{,<channel>}] [<elistcond>{,<elistcond>}]
}

void	privmsg_cmd()
{
	// Pour envoyer des messages prives entre utilisateurs

	// Parameters: <target>{,<target>} <text to be sent>
}

void	invite_cmd()
{
	// Commande utilisee pour inviter un utilisateur dans un channel

	// Parameters: <nickname> <channel>
}

void	quit_cmd()
{
	// Commande utilise pour mettre fin a la connexion du client
	// sur le serveur

	// Parameters: [<reason>]
}

void	mode_cmd()
{
	// On l'utilise pour mettre ou enlever des options (ou modes)
	// d'une target donne.

	// Parameters: <target> [<modestring> [<mode arguments>...]]
}

void	topic_cmd()
{
	// On l'utilise pour changer ou voir un topic du channel donne.

	// Parameters: <channel> [<topic>]
}

void	names_cmd()
{
	// On l'utilise pour afficher les nicknameslie a un channel et leur prefixes.

	// Parameters: <channel>{,<channel>}
}

void	kick_cmd()
{
	// Peut etre utilise pour demander de supprimer de force 
	// un utilisateur dans un channel

	// Parameters: <channel> <user> *("," <user>) [<comment>]
}
