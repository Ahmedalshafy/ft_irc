#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

#include <string>

// Error Replies (400-599)
#define ERR_NOSUCHCHANNEL(nick, channel) "403 " + nick + " " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(nick, channel) "404 " + nick + " " + channel + " :Cannot send to channel"
#define ERR_TOOMANYCHANNELS(nick, channel) "405 " + nick + " " + channel + " :You have joined too many channels"
#define ERR_NONICKNAMEGIVEN(nick) "431 " + nick + " :No nickname given"
#define ERR_ERRONEUSNICKNAME(nick) "432 " + nick + " :Erroneous nickname"
#define ERR_NICKNAMEINUSE(nick) "433 " + nick + " :Nickname is already in use"
#define ERR_NOTONCHANNEL(nick, channel) "442 " + nick + " " + channel + " :You're not on that channel"
#define ERR_NOTREGISTERED(nick) "451 " + nick + " :You have not registered"
#define ERR_NEEDMOREPARAMS(nick, command) "461 " + nick + " " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(nick) "462 " + nick + " :You may not reregister"
#define ERR_CHANNELISFULL(nick, channel) "471 " + nick + " " + channel + " :Cannot join channel (+l)"
#define ERR_UNKNOWNMODE(nick, mode) "472 " + nick + " " + mode + " :is unknown mode char to me"
#define ERR_INVITEONLYCHAN(nick, channel) "473 " + nick + " " + channel + " :Cannot join channel (+i)"
#define ERR_BANNEDFROMCHAN(nick, channel) "474 " + nick + " " + channel + " :Cannot join channel (+b)"
#define ERR_BADCHANNELKEY(nick, channel) "475 " + nick + " " + channel + " :Cannot join channel (+k)"

// Command Responses (200-399)
#define RPL_WELCOME(nick) "001 " + nick + " :Welcome to the Internet Relay Network " + nick
#define RPL_NAMREPLY(nick, channel, users) "353 " + nick + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(nick, channel) "366 " + nick + " " + channel + " :End of /NAMES list"
#define RPL_CHANNELMODEIS(nick, channel, mode) "324 " + nick + " " + channel + " " + mode

#endif // NUMERIC_REPLIES_HPP
