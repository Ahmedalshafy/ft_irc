/**
 * @file topicCommand.cpp
 * @brief Implementation of IRC TOPIC command
 * 
 * This file implements the TOPIC command handler which allows viewing and setting
 * channel topics. It follows RFC 2812 specifications for topic management and
 * access control.
 */

#include "../Includes/Server.hpp"

/**
 * @brief Handle the TOPIC command
 * @param client Pointer to the client issuing the command
 * @param ParsedMsg Parsed message containing command parameters
 * 
 * Command format: TOPIC <channel> [<topic>]
 * 
 * Functionality:
 * 1. View current topic: TOPIC <channel>
 * 2. Change topic: TOPIC <channel> :<new topic>
 * 
 * Access Control:
 * - All users can view the topic
 * - If channel mode +t is set, only operators can change topic
 * - User must be in the channel to use TOPIC command
 * 
 * Error Handling:
 * - Channel doesn't exist
 * - User not in channel
 * - Insufficient privileges (with +t mode)
 * - Missing parameters
 */
void Server::topicCommand(Client *client, const ParseMessage &ParsedMsg)
{
    std::vector<std::string> params = ParsedMsg.getParams();
    std::string response = "";
    std::string channelName;
    std::string newTopic;

    // Validate required parameters
    if (params.empty()) {
        client->getServerReplies().push_back(ERR_NEEDMOREPARAMS(client->getNickname(), "TOPIC"));
        return;
    }

    // Get and validate channel name
    channelName = params[0];
    if (channelName[0] != '#' && channelName[0] != '&') {
        return;  // Invalid channel prefix
    }

    // Check if channel exists
    if (!isChannelInServer(channelName)) {
        response = ERR_NOSUCHCHANNEL(client->getNickname(), channelName);
        client->getServerReplies().push_back(response);
        return;
    }

    Channel &channel = getChannel(channelName);

    // Verify user is in the channel
    if (!channel.isClientInChannel(client->getNickname())) {
        response = ERR_NOTONCHANNEL(client->getNickname(), channelName);
        client->getServerReplies().push_back(response);
        return;
    }

    // Handle topic query (no new topic provided)
    if (ParsedMsg.getTrailing().empty()) {
        if (channel.getTopic().empty()) {
            response = RPL_NOTOPIC(client->getNickname(), channelName);
        } else {
            response = RPL_TOPIC(client->getNickname(), channelName, channel.getTopic());
        }
        client->getServerReplies().push_back(response);
        return;
    }

    // Check topic change permissions
    if (channel.checkMode('t') && !channel.isOperator(client->getNickname())) {
        response = ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName);
        client->getServerReplies().push_back(response);
        return;
    }

    // Set new topic and broadcast change
    newTopic = ParsedMsg.getTrailing();
    std::string topicChangeMsg;
    channel.setTopic(newTopic);
    topicChangeMsg = RPL_CHANGETOPIC(user_id(client->getNickname(), client->getUsername()), 
                                   channel.getChannelName(), 
                                   newTopic);
    channel.broadcastMessage(topicChangeMsg);
}
