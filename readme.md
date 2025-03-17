port beetween 0 && 65535 : TCP (16-bit)

Ports 0 to 1023 are reserved for specific services and protocols, such as HTTP (port 80), FTP (port 21), and SSH (port 22). They require administrative privileges to use

Ports numbered 1024 to 49151 can be registered for specific purposes and are used by non-standard applications and services.

Dynamic or private ports (49152 to 65535) are used by client applications for outgoing connections. These ports are dynamically allocated by the operating system to clients when they initiate outgoing connections.

////////
irssi
/connect localhost 6667

NetCat : 

apres make pass 
```bash
echo -ne "PASS mdp\r\nNICK monPseudo\r\nUSER monPseudo 0 * :Mon Nom\r\n" | nc localhost 6667
```
apres make run
```bash 
echo -ne "NICK monPseudo\r\nUSER monPseudo 0 * :Mon Nom\r\n" | nc localhost 6667
```