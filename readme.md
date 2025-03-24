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

# **IRC Server en C++98**

Ce projet implémente un **serveur IRC** basique en **C++98** qui gère les connexions clients, les canaux et la communication entre utilisateurs. Il repose sur le protocole IRC et utilise `poll()` pour la gestion des connexions réseau.

## **Structure du projet**

### **1. Client.hpp** (Gestion des utilisateurs)
Ce fichier définit la classe `Client`, qui représente un utilisateur connecté au serveur.  
Un client possède :
- Un **pseudo** et un **vrai nom** (`_nickName`, `_realName`).
- Un **file descriptor** (`_fd`) pour la communication réseau.
- Son **adresse IP** (`_IPadd`).
- Un historique des commandes envoyées (`historic`).
- Une liste des canaux auxquels il est connecté (`channelsList`).
- Un état d'**authentification** (`_authenticated`).

#### **Méthodes importantes :**
- `setNickname()`, `setRealName()` → Définit les informations utilisateur.
- `addChannelToList()`, `removeChannelToList()` → Gère l'inscription aux canaux.
- `ReceiveMessage()` → Récupère les données envoyées par l'utilisateur.

---

### **2. Channel.hpp** (Gestion des canaux)
Ce fichier définit la classe `Channel`, qui représente un **salon IRC**.  
Chaque canal possède :
- Un **nom** (`_name`).
- Un **sujet** (`topic`).
- Une **liste des utilisateurs** (`users`).
- Une **liste des opérateurs** (`operators`).
- Une **liste des invitations** (`invitations`).
- Un **mot de passe** (`password`).
- Un **nombre limite d’utilisateurs** (`userLimit`).
- Un tableau de **modes activés** (`modes`).
- Une **date de création** (`creationTime`).

#### **Méthodes importantes :**
- `addClient()`, `addOperator()`, `addInvitation()` → Ajoute des utilisateurs.
- `isClientConnected()`, `isClientOperator()`, `isClientInvited()` → Vérifie les droits.
- `kickClient()`, `kickOperator()` → Éjecte un utilisateur du canal.

---

### **3. Server.hpp** (Gestion du serveur)
Ce fichier définit la classe `Server`, qui représente le serveur IRC.  
Le serveur gère :
- Les connexions sur un **port donné** (`_Port`).
- Une **liste de clients connectés** (`clients`).
- Une **liste de canaux** (`channels`).
- La gestion des **erreurs** (`errors`).
- Le **mot de passe du serveur** (`_password`).
- Les **événements réseau** avec `poll()` (`fds`).

#### **Méthodes importantes :**
- `Init()` → Initialise le socket du serveur.
- `Run()` → Boucle principale qui gère les connexions et la communication.
- `AcceptNewClient()` → Accepte un nouvel utilisateur.
- `kickClient()` → Déconnecte un client.
- `sendMessage()` → Envoie un message aux utilisateurs d’un canal.
- `HandleNewData()` → Analyse les commandes envoyées par les clients.
- `SignalHandler()` → Gère les interruptions système (`CTRL+C`).

---

## **Fonctionnalités**
- **Connexion des utilisateurs** avec gestion des pseudos.
- **Création et gestion des canaux** (avec opérateurs, invitations, etc.).
- **Gestion des permissions et de l'authentification**.
- **Système de communication IRC basique**.
- **Utilisation de `poll()`** pour la gestion des connexions multiples.

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
