
# **FT_IRC**

FT_IRC is a simple implementation of an **IRC (Internet Relay Chat) server** in C++.
This project aims to provide a basic understanding of how IRC servers work and how they can be implemented from scratch.

## **Getting Started**

### **Prerequisites**

- A **C++ compiler**
- `make`

### **Compiling the Project**

To compile the project, navigate to the project directory and run:

```bash
make
```

### **Running the Server**

You can start the server with the following commands:

#### **With Password**

```bash
make pass
```

#### **Without Password**

```bash
make run
```

---

## **Usage**

### **Connecting with NetCat**

You can connect to the server using **NetCat** with the following commands:

#### **With Password**

```bash
echo -ne "PASS password\r\nNICK myNickname\r\nUSER myNickname 0 * :My Name\r\n" | nc localhost 6667
```

#### **Without Password**

```bash
echo -ne "NICK myNickname\r\nUSER myNickname 0 * :My Name\r\n" | nc localhost 6667
```

### **Connecting with Irssi**

You can also connect to the server using **Irssi**, a popular IRC client:

#### **With Password**

```bash
irssi -c localhost -p 6667 -w password -n myNickname
```

#### **Without Password**

```bash
irssi -c localhost -p 6667 -n myNickname
```

---

# **IRC Server in C++98**

This project implements a basic **IRC server** in **C++98**, capable of handling client connections, channels, and user communication. It follows the **IRC protocol** and uses `poll()` for managing multiple connections.

## **Project Structure**

### **1. Client.hpp** (User Management)

This file defines the `Client` class, which represents a user connected to the server.

Each client has:
- A **nickname** and **real name** (`_nickName`, `_realName`).
- A **file descriptor** (`_fd`) for network communication.
- An **IP address** (`_IPadd`).
- A **command history** (`historic`).
- A **list of channels** they are connected to (`channelsList`).
- An **authentication status** (`_authenticated`).

#### **Key Methods:**
- `setNickname()`, `setRealName()` → Sets user information.
- `addChannelToList()`, `removeChannelToList()` → Manages channel subscriptions.
- `ReceiveMessage()` → Retrieves data sent by the user.

---

### **2. Channel.hpp** (Channel Management)

This file defines the `Channel` class, which represents an **IRC chat room**.

Each channel has:
- A **name** (`_name`).
- A **topic** (`topic`).
- A **list of users** (`users`).
- A **list of operators** (`operators`).
- A **list of invitations** (`invitations`).
- A **password** (`password`).
- A **user limit** (`userLimit`).
- An **array of active modes** (`modes`).
- A **creation timestamp** (`creationTime`).

#### **Key Methods:**
- `addClient()`, `addOperator()`, `addInvitation()` → Adds users.
- `isClientConnected()`, `isClientOperator()`, `isClientInvited()` → Checks permissions.
- `kickClient()`, `kickOperator()` → Removes users from the channel.

---

### **3. Server.hpp** (Server Management)

This file defines the `Server` class, which represents the IRC server.

The server handles:
- Connections on a **specific port** (`_Port`).
- A **list of connected clients** (`clients`).
- A **list of channels** (`channels`).
- **Error management** (`errors`).
- The **server password** (`_password`).
- **Network events** with `poll()` (`fds`).

#### **Key Methods:**
- `Init()` → Initializes the server socket.
- `Run()` → Main loop handling connections and communication.
- `AcceptNewClient()` → Accepts new users.
- `kickClient()` → Disconnects a client.
- `sendMessage()` → Sends a message to channel users.
- `HandleNewData()` → Parses user commands.
- `SignalHandler()` → Handles system interrupts (`CTRL+C`).

---

## **Features**

- **User connections** with nickname management.
- **Channel creation and management** (operators, invitations, etc.).
- **Authentication and permission system**.
- **Basic IRC communication system**.
- **Use of `poll()`** for managing multiple connections.

---

## **Implemented Commands**

FT_IRC supports several **standard IRC commands**, allowing users to interact with the server and each other.

### **Basic Commands**
- **PASS `<password>`** → Sets the password to connect to the server (if required).
- **NICK `<nickname>`** → Sets or changes the user’s nickname.
- **USER `<username> 0 * :<real_name>`** → Identifies a user to the server.
- **QUIT [<message>]** → Disconnects from the server with an optional message.

### **Channel Management Commands**
- **JOIN `<#channel>`** → Joins a channel.
- **PART `<#channel>` [<message>]** → Leaves a channel with an optional message.
- **TOPIC `<#channel>` [<new_topic>]** → Retrieves or changes a channel’s topic.
- **MODE `<#channel> [<mode>] [<parameters>]`** → Changes channel or user modes.
- **INVITE `<user> <#channel>`** → Invites a user to a channel.
- **KICK `<#channel> <user> [<message>]`** → Kicks a user from a channel.

### **Communication Commands**
- **PRIVMSG `<target>` `<message>`** → Sends a private message to a user or channel.

### **Information Commands**
- **WHO `<target>`** → Lists users in a channel or retrieves user information.
- **WHOIS `<user>`** → Displays detailed information about a user.
- **VERSION** → Returns the IRC server version.
- **PING `<message>`** → Checks the connection with the server.
- **PONG `<message>`** → Responds to a server PING request.


---

# **FT_IRC**  

FT_IRC est une implémentation simple d’un **serveur IRC (Internet Relay Chat)** en C++.  
Ce projet vise à fournir une compréhension de base du fonctionnement des serveurs IRC et de leur mise en œuvre à partir de zéro.  

## **Démarrage**  

### **Prérequis**  

- Un **compilateur C++**  
- `make`  

### **Compilation du projet**  

Pour compiler le projet, accédez au répertoire du projet et exécutez :  

```bash
make
```

### **Exécution du serveur**  

Vous pouvez lancer le serveur avec les commandes suivantes :  

#### **Avec mot de passe**  

```bash
make pass
```

#### **Sans mot de passe**  

```bash
make run
```

---

## **Utilisation**  

### **Connexion avec NetCat**  

Vous pouvez vous connecter au serveur avec **NetCat** en utilisant les commandes suivantes :  

#### **Avec mot de passe**  

```bash
echo -ne "PASS mdp\r\nNICK monPseudo\r\nUSER monPseudo 0 * :Mon Nom\r\n" | nc localhost 6667
```

#### **Sans mot de passe**  

```bash
echo -ne "NICK monPseudo\r\nUSER monPseudo 0 * :Mon Nom\r\n" | nc localhost 6667
```

### **Connexion avec Irssi**  

Vous pouvez également vous connecter au serveur avec **Irssi**, un client IRC populaire :  

#### **Avec mot de passe**  

```bash
irssi -c localhost -p 6667 -w mdp -n monPseudo
```

#### **Sans mot de passe**  

```bash
irssi -c localhost -p 6667 -n monPseudo
```

---

# **Serveur IRC en C++98**  

Ce projet implémente un **serveur IRC** basique en **C++98**, capable de gérer les connexions clients, les canaux et la communication entre utilisateurs. Il repose sur le **protocole IRC** et utilise `poll()` pour gérer les connexions multiples.  

## **Structure du projet**  

### **1. Client.hpp** (Gestion des utilisateurs)  

Ce fichier définit la classe `Client`, qui représente un utilisateur connecté au serveur.  

Chaque client possède :  
- Un **pseudo** et un **nom réel** (`_nickName`, `_realName`).  
- Un **file descriptor** (`_fd`) pour la communication réseau.  
- Son **adresse IP** (`_IPadd`).  
- Un **historique des commandes envoyées** (`historic`).  
- Une **liste des canaux** auxquels il est connecté (`channelsList`).  
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
- `kickClient()`, `kickOperator()` → Expulse un utilisateur du canal.  

---

### **3. Server.hpp** (Gestion du serveur)  

Ce fichier définit la classe `Server`, qui représente le serveur IRC.  

Le serveur gère :  
- Les connexions sur un **port donné** (`_Port`).  
- Une **liste des clients connectés** (`clients`).  
- Une **liste des canaux** (`channels`).  
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

## **Commandes Implémentées**  

FT_IRC prend en charge plusieurs **commandes IRC standard**, permettant aux utilisateurs d’interagir avec le serveur et entre eux.  

### **Commandes de base**  
- **PASS `<mot_de_passe>`** → Définit le mot de passe pour se connecter au serveur (si requis).  
- **NICK `<pseudo>`** → Définit ou change le pseudo de l'utilisateur.  
- **USER `<nom_utilisateur> 0 * :<nom_réel>`** → Identifie un utilisateur auprès du serveur.  
- **QUIT [<message>]** → Permet de quitter le serveur avec un message optionnel.  

### **Commandes de gestion des canaux**  
- **JOIN `<#channel>`** → Rejoint un canal.  
- **PART `<#channel>` [<message>]** → Quitte un canal avec un message optionnel.  
- **TOPIC `<#channel>` [<nouveau_sujet>]** → Récupère ou modifie le sujet d’un canal.  
- **MODE `<#channel> [<mode>] [<paramètres>]`** → Change les modes d’un canal ou d’un utilisateur.  
- **INVITE `<utilisateur> <#channel>`** → Invite un utilisateur à rejoindre un canal.  
- **KICK `<#channel> <utilisateur> [<message>]`** → Expulse un utilisateur d’un canal.  

### **Commandes de communication**  
- **PRIVMSG `<cible>` `<message>`** → Envoie un message privé à un utilisateur ou un canal.  

### **Commandes d’information**  
- **WHO `<cible>`** → Affiche la liste des utilisateurs connectés dans un canal ou des informations sur un utilisateur.  
- **WHOIS `<utilisateur>`** → Affiche des informations détaillées sur un utilisateur.  
- **VERSION** → Renvoie la version du serveur IRC.  
- **PING `<message>`** → Vérifie la connexion avec le serveur.  
- **PONG `<message>`** → Répond à une requête PING du serveur.  

---
