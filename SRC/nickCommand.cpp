#include "../Includes/Server.hpp"



void 	Server::nickCommand(Client *client, const std::vector<std::string> &params)
{
	//check its not empty
	//check if nickname not in use already
	//check nickname doest contain these find_first_of("# @:&")
	//if it checks out then add to nicknames vector
	//erase the current nickname from nickname list
	//send message with nickname reply
	//clear then add the new nickname
	if(params.size() < 1)
	{
       client->serverReplies.push_back(ERR_NONICKNAMEGIVEN(std::string("ircserver")));
		return ;
	}
	std::string newNick = params[0]; //also new nick could be getTrailing()
    if (newNick.find_first_of("#@:&") != std::string::npos)
    {
       client->serverReplies.push_back(ERR_ERRONEUSNICKNAME(std::string("ircserver"), newNick));
	   return ;
    }
    else if (_nicknames.empty() == false && std::find(_nicknames.begin(), _nicknames.end(), newNick) != _nicknames.end())
    {
       client->serverReplies.push_back(ERR_NICKNAMEINUSE(std::string("ircserver"), newNick));
	   return ;
    } 
    else if (client->getNickname().empty() == false)
    {
        _nicknames.erase(std::remove(_nicknames.begin(), _nicknames.end(),client->getNickname()), _nicknames.end());
       client->serverReplies.push_back(RPL_NICK(client->getNickname(),client->getUsername(), newNick));
    }
	_nicknames.push_back(newNick);
	//add function update nicknames in channels
	// Check all channels in server where that client is joined currently
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->second.isClientInChannel(client->getNickname()))
		{	
			it->second.updateNickname(client->getNickname(), newNick);
		} else if (it->second.isInvited(client->getNickname()))
		{
			it->second.updateNickname(client->getNickname(), newNick);
		}
	}
	// If client is in channel, update the nickname in that channel

	client->setNickname(newNick);
}