/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:26:34 by mahmoud           #+#    #+#             */
/*   Updated: 2024/10/21 15:06:24 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>  // for std::find and std::remove
#include <cctype>     // for isdigit and isalnum
// #include "Client.hpp"

class Client;
class Channel;

// MESSAGE FORMAT:
# define idFormat(nickname, username) (":" + nickname + "!" + username + "@localhost")


// NICKNAME ERRORS:
#define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " ::No nickname given.\r\n")

#define ERR_NICKNAMEINUSE(client, nickname) (":localhost 433 " + client + " " + nickname + " :Nickname is already in use.\r\n")

#define ERR_ERRONEUSNICKNAME(client, nickname) (":localhost 432 " + client + " " + nickname + " :Erroneous nickname\r\n")

// GENERAL ERRORS:
# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters.\r\n")

#define ERROR_MESSAGE(reason) ("ERROR :" + reason + "\r\n")

// PASSWORD ERRORS:
#define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect.\r\n")

// USER ERRORS:
#define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :Already registered.\r\n")

// CONNECTION REGISTRATION SUCCESS MESSAGES TO SEND:
# define RPL_WELCOME(idFormat, nickname) (":localhost 001 " + nickname + " :Welcome to the Internet Relay Network " + idFormat + "\r\n")
# define RPL_YOURHOST(client, servername, version) (":localhost 002 " + client + " :Your host is " + servername + " (localhost), running version " + version + "\r\n")
# define RPL_CREATED(client, datetime) (":localhost 003 " + client + " :This server was created " + datetime + "\r\n")
# define RPL_MYINFO(client, servername, version, user_modes, chan_modes, chan_param_modes) (":localhost 004 " + client + " " + servername + " " + version + " " + user_modes + " " + chan_modes + " " + chan_param_modes + "\r\n")
# define RPL_ISUPPORT(client, tokens) (":localhost 005 " + client + " " + tokens " :are supported by this server\r\n")

#define RPL_NICK(oclient, uclient, client) (":" + oclient + "!" + uclient + "@localhost NICK " +  client + "\r\n")

#define RPL_PONG(idFormat, token) (idFormat + " PONG " + token + "\r\n")

#define RPL_MOTDSTART(client, servername) (":localhost 375 " + client + " :- " + servername + " Message of the day - \r\n")

#define RPL_MOTD(client, motd_line) (":localhost 372 " + client + " :" + motd_line + "\r\n")

#define ERR_NOMOTD(client) (":localhost 422 " + client + " :MOTD File is missing\r\n")

#define RPL_ENDOFMOTD(client) (":localhost 376 " + client + " :End of /MOTD command.\r\n")

#define ERR_USERONCHANNEL(username, nickname, channel) (":localhost 443 " + username + " " + nickname + " " + channel + " :is already on channel\r\n")
#define ERR_CHANNELISFULL(client, channel) (":localhost 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(client, channel) (":localhost 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(client, channel) (":localhost 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
#define RPL_JOIN(idFormat, channel) (idFormat + " JOIN " + channel + "\r\n")
#define RPL_TOPIC(client, channel, topic) (":localhost 332 " + client + " " + channel + " :" + topic + "\r\n")
#define RPL_NOTOPIC(client, channel) (":localhost 331 " + client + " " + channel + " :No topic is set\r\n")
#define RPL_NAMREPLY(client, channel, users) (":localhost 353 " + client + " = " + channel + " :" + users + "\r\n")
#define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " " + channel + " :End of /NAMES list.\r\n")

#define MAX_CLIENTS 100

class Server {
public:
    Server(int port, const std::string& password);
    void run();

private:
    int listenSocket;
    int port;
    std::string serverPassword;
    volatile sig_atomic_t running;
    std::string serverStartTime;
    std::map<std::string, Channel> channels;  // Map to store channels

    // Socket and client handling
    void setupSocket();
    void acceptClient(int &clientCount, std::map<int, Client> &clients, struct pollfd fds[]);
    void handleClientInput(int i, int &clientCount, std::map<int, Client> &clients, struct pollfd fds[], std::string serverStartTime);
    void removeClientFD(int i, int &clientCount, std::map<int, Client> &clients, struct pollfd fds[]);
    void cleanupClients(int clientCount, struct pollfd fds[]);
    std::string getCurrentDateTime();

    // Channel management functions
    bool isChannelInServer(const std::string& channelName) const;
    Channel& getChannel(const std::string& channelName);
    const Channel& getChannel(const std::string& channelName) const;

    // Command handlers
    void handleJoinCommand(Client *client, const std::vector<std::string> &params);
};

#endif // SERVER_HPP
