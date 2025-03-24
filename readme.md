# FT_IRC

FT_IRC is a simple IRC (Internet Relay Chat) server implementation in C++. This project aims to provide a basic understanding of how IRC servers work and how to implement one from scratch.

## Getting Started

### Prerequisites

- C++ compiler
- Make

### Building the Project

To build the project, navigate to the project directory and run:

```bash
make
```

### Running the Project

You can run the server with:

#### With Password

```bash
make pass
```

#### Without Password

```bash
make run
```

## Usage

### Connecting with NetCat

You can connect to the server using NetCat with the following commands:

#### With Password

```bash
echo -ne "PASS mdp\r\nNICK monPseudo\r\nUSER monPseudo 0 * :Mon Nom\r\n" | nc localhost 6667
```

#### Without Password

```bash
echo -ne "NICK monPseudo\r\nUSER monPseudo 0 * :Mon Nom\r\n" | nc localhost 6667
```

### Connecting with Irssi

You can also connect to the server using Irssi, a popular IRC client:

#### With Password

```bash
irssi -c localhost -p 6667 -w mdp -n monPseudo
```

#### Without Password

```bash
irssi -c localhost -p 6667 -n monPseudo
```

---

## Commandes Implémentées  

FT_IRC prend en charge plusieurs commandes IRC standard permettant aux utilisateurs d'interagir avec le serveur et entre eux.  

### Commandes de base  
- **PASS `<mot_de_passe>`** : Définit le mot de passe pour se connecter au serveur (si requis).  
- **NICK `<pseudo>`** : Définit ou change le pseudo de l'utilisateur.  
- **USER `<nom_utilisateur> 0 * :<nom_réel>`** : Identifie un utilisateur auprès du serveur.  
- **QUIT [<message>]** : Permet de quitter le serveur avec un message optionnel.  

### Commandes de gestion des canaux  
- **JOIN `<#channel>`** : Rejoint un canal.  
- **PART `<#channel>` [<message>]** : Quitte un canal avec un message optionnel.  
- **TOPIC `<#channel>` [<nouveau_sujet>]** : Récupère ou modifie le sujet d’un canal.  
- **MODE `<#channel> [<mode>] [<paramètres>]`** : Change les modes d’un canal ou d’un utilisateur.  
- **INVITE `<utilisateur> <#channel>`** : Invite un utilisateur à rejoindre un canal.  
- **KICK `<#channel> <utilisateur> [<message>]`** : Expulse un utilisateur d’un canal.  

### Commandes de communication  
- **PRIVMSG `<cible>` `<message>`** : Envoie un message privé à un utilisateur ou un canal.  

### Commandes d’information  
- **WHO `<cible>`** : Affiche la liste des utilisateurs connectés dans un canal ou des informations sur un utilisateur.  
- **WHOIS `<utilisateur>`** : Affiche des informations détaillées sur un utilisateur.  
- **VERSION** : Renvoie la version du serveur IRC.  
- **PING `<message>`** : Vérifie la connexion avec le serveur.  
- **PONG `<message>`** : Répond à une requête PING du serveur.  



