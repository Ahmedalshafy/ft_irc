# include "Client.hpp"
# include "Server.hpp"
# include "Utils.hpp"
# include "Channels.hpp"
# include "NumericReplies.hpp"
# include <sstream>

void Server::handleInviteCommand(Client *client, const std::vector<std::string> &params)
{
    std::string response = "";
	std::string targetNickname;
	std::string channelName;

    if (params.size() < 2) {
        client->addInServerReplies(ERR_NEEDMOREPARAMS(client->getNickname(), "INVITE"));
        return;
    }
    targetNickname = params[0];
    channelName = params[1];
    if (channelName.at(0) != '#' && channelName.at(0) != '&') {
        response = ERR_NOSUCHCHANNEL(client->getNickname(), channelName);
        client->addInServerReplies(response);
        return;
    }
    if (!isChannelInServer(channelName)) {
        response = ERR_NOSUCHCHANNEL(client->getNickname(), channelName);
        client->addInServerReplies(response);
        return;
    }

    Channel &channel = getChannel(channelName);

    if (!channel.isClientInChannel(client->getNickname())) {
        response = ERR_NOTONCHANNEL(client->getNickname(), channelName);
        client->addInServerReplies(response);
        return;
    }

    if (channel.checkMode('i') && !channel.isOperator(client->getNickname())) {
        response = ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName);
        client->addInServerReplies(response);
        return;
    }

    Client *targetClient = getClient(targetNickname);
    if (!targetClient) {
        response = ERR_NOSUCHNICK(client->getNickname(), targetNickname);
        client->addInServerReplies(response);
        return;
    }
    if (channel.isClientInChannel(targetClient->getNickname())) {
        response = ERR_USERONCHANNEL(client->getNickname(), targetNickname, channelName);
        client->addInServerReplies(response);
        return;
    }
	channel.inviteClient(targetClient);
    response = RPL_INVITE(user_id(client->getNickname(), client->getUsername()), targetClient->getNickname(), channelName);
    targetClient->addInServerReplies(response);
	std::string inviteMessage = RPL_INVITING(user_id(client->getNickname(),  client->getUsername()), client->getNickname(), targetNickname, channelName);
    client->addInServerReplies(inviteMessage);
}