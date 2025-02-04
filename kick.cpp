# include "Client.hpp"
# include "Server.hpp"
# include "Utils.hpp"
# include "Channels.hpp"
# include "NumericReplies.hpp"
# include <sstream>

void Server::handleKickCommand(Client *client, const std::vector<std::string> &params)
{
    if (params.size() < 2) {
        client->addInServerReplies(ERR_NEEDMOREPARAMS(client->getNickname(), "KICK"));
        return;
    }

    std::string trailingMessage = ParsedMsg.getTrailing().empty() ? "" :  ParsedMsg.getTrailing();
    std::string channelName = params[0];


    if (!isChannelInServer(channelName)) {
        client->addInServerReplies(ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
        return;
    }
    Channel &channel = getChannel(channelName);

    if (!channel.isClientInChannel(client->getNickname())) {
        client->addInServerReplies(ERR_NOTONCHANNEL(client->getNickname(), channelName));
        return;
    }

    if (!channel.isOperator(client->getNickname())) {
        client->addInServerReplies(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName));
        return;
    }

    std::vector<std::string> users = ft_split(params[1] , ',');

    for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it)
    {
        std::string targetNick = *it;
        // Check if the client is trying to kick themselves
        if (targetNick == client->getNickname()) {
            client->addInServerReplies(": localhost  482 " + client->getNickname() + " " + channelName + " :You can't kick yourself\r\n");
            continue;
        }
        Client *targetClient = getClient(targetNick);

        if (!targetClient || !channel.isClientInChannel(targetNick)) {
            client->addInServerReplies(ERR_USERNOTINCHANNEL(client->getNickname(), targetNick, channelName));
            continue;
        }

        std::string kickMsg = RPL_KICK(user_id(client->getNickname(), client->getUsername()), channelName, targetClient->getNickname(), trailingMessage);
        channel.sendTo_all(kickMsg);
        channel.remove(targetClient);

        if (channel.getUsers().empty()) {
            channels.erase(channelName);
        }
    }
}