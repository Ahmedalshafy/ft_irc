/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:26:34 by mahmoud           #+#    #+#             */
/*   Updated: 2025/02/04 16:32:38 by aalshafy         ###   ########.fr       */
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
#include "Channel.hpp"
#include "NumericReplies.hpp"

class Client;
class Channel;

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
    std::map<int, Client*> clients;           // Map to store clients
    
    // Socket and client handling
    void setupSocket();
    void acceptClient(int &clientCount, std::map<int, Client> &clients, struct pollfd fds[]);
    void handleClientInput(int i, int &clientCount, std::map<int, Client> &clients, struct pollfd fds[], std::string serverStartTime);
    void removeClientFD(int i, int &clientCount, std::map<int, Client> &clients, struct pollfd fds[]);
    void cleanupClients(int clientCount, struct pollfd fds[]);
    std::string getCurrentDateTime();
    Client *getClient(std::string nickname);

    // Channel management functions
    void addChannel(const std::string& channelName, Channel &channel);
    void removeChannel(const std::string& channelName);
    bool isChannelInServer(const std::string& channelName) const;
    Channel& getChannel(const std::string& channelName);
    const Channel& getChannel(const std::string& channelName) const;
    std::string Server::greetJoinedUser(Client &client, Channel &channel);


    // Command handlers
    void handleInviteCommand(Client *client, const std::vector<std::string> &params);
    void handleJoinCommand(Client *client, const std::vector<std::string> &params);
    void quitCommand(std::string reason, Client *client);
    void handlePartCommand(Client *client, const std::vector<std::string> &params);
    void handleNickCommand(Client *client, const std::vector<std::string> &params);
    void handleUserCommand(Client *client, const std::vector<std::string> &params);
    void handlePrivmsgCommand(Client *client, const std::vector<std::string> &params);
    void Server::handelModeCommand(Client *client, const ParseMessage &parsedMsg);
    bool Server::handleKeyMode(Client *client, Channel &channel, bool isAdding,
	  std::vector<std::string> &params, std::size_t &paramIndex);
    void handleCapCommand(Client *client, const std::vector<std::string> &params);
    bool Server::handleLimitMode(Client *client, Channel &channel, bool isAdding,
	  std::vector<std::string> &params, std::size_t &paramIndex);
    bool Server::handleOperatorMode(Client *client, Channel &channel, bool isAdding,
	  std::vector<std::string> &params, std::size_t &paramIndex);
    bool Server::processSingleChannelMode(Client *client, Channel &channel,
	char mode, bool isAdding,   std::vector<std::string> &params,
	std::size_t &paramIndex);
    void Server::processChannelModes(Client *client, Channel &channel,
	  std::vector<std::string> &params);
    void Server::handleChannelMode(Client *client, std::string &channelName,
	  std::vector<std::string> &params);
    bool Server::isUserInServer(const std::string &nickname);  

};

#endif // SERVER_HPP
