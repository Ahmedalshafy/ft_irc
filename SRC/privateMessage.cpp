/**
 * @file privateMessage.cpp
 * @brief Implementation of IRC PRIVMSG command
 * 
 * This file implements the PRIVMSG command handler which allows sending messages
 * to both channels and individual users. It follows RFC 2812 specifications
 * for message delivery and access control.
 */

#include "../Includes/Channel.hpp"

/**
 * @brief Handle the PRIVMSG command
 * @param client Pointer to the client sending the message
 * @param parsedMsg Parsed message containing command parameters
 * 
 * Command format: PRIVMSG <receiver> :<text>
 * 
 * Supports two types of messages:
 * 1. Channel messages: PRIVMSG #channel :<text>
 *    - Message is broadcast to all channel members except sender
 *    - Sender must be in the channel
 * 
 * 2. Private messages: PRIVMSG nickname :<text>
 *    - Message is sent to a specific user
 *    - Target user must exist on the server
 * 
 * Error Handling:
 * - No recipient specified
 * - No message text
 * - Channel doesn't exist
 * - User not in channel
 * - Target user doesn't exist
 */
void Server::privateMessage(Client *client, const ParseMessage &parsedMsg)
{
    const std::vector<std::string>& params = parsedMsg.getParams();
    const std::string& trailing = parsedMsg.getTrailing();
	std::string receiver; 

    // Validate required parameters
    if (params.empty() || trailing.empty())
    {
        if (params.empty())
            client->getServerReplies().push_back(ERR_NORECIPIENT(client->getNickname()));
        else
            client->getServerReplies().push_back(ERR_NOTEXTTOSEND(client->getNickname()));
        return;
    }

	if(params.empty() == false)
	{
		receiver = params[0];
	}

    // Handle channel messages
    if(receiver[0] == '#' || receiver[0] == '&') //potential segfault here for receiver
    {
        // Validate channel exists
        if (!isChannelInServer(receiver))
        {
            client->getServerReplies().push_back(ERR_CANNOTSENDTOCHAN(client->getNickname(), receiver));
            return;
        }

        Channel &channel = getChannel(receiver);
        
        // Check if sender is in channel
        if (!channel.isClientInChannel(client->getNickname()))
        {
            client->getServerReplies().push_back(ERR_CANNOTSENDTOCHAN(client->getNickname(), receiver));
            return;
        }
        // Broadcast message to all channel members except sender
        channel.sendToOthers(client, RPL_PRIVMSG(client->getNickname(), client->getNickname(), receiver, trailing));
    }
    // Handle private messages
    else
    {
        // Validate target user exists
        if (!isUserInServer(receiver))
        {
            client->getServerReplies().push_back(ERR_NOSUCHNICK(client->getNickname(), receiver));
            return;
        }
        // Send private message to recipient
        Client *recipientClient = getClient(receiver);
        recipientClient->getServerReplies().push_back(RPL_PRIVMSG(client->getNickname(), client->getUsername(), receiver, trailing));
    }
}