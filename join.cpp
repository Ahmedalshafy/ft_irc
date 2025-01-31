# include "Client.hpp"
# include "Server.hpp"
# include "Utils.hpp"
# include "Channels.hpp"
# include "NumericReplies.hpp"
# include <sstream>

std::string greetJoinedUser(Client &client, Channel &channel) {
    std::string response;
    
    // Send topic if exists
    if (!channel.GetTopicName().empty())
        response += RPL_TOPIC(client.getNickname(), channel.GetName(), channel.GetTopicName());
    else
        response += RPL_NOTOPIC(client.getNickname(), channel.GetName());
    
    // Send names list
    response += RPL_NAMREPLY(client.getNickname(), channel.GetName(), channel.clientChannel_list());
    response += RPL_ENDOFNAMES(client.getNickname(), channel.GetName());
    
    return response;
}

void Server::handleJoinCommand(Client *client, const std::vector<std::string> &params)
{
    std::vector<std::string> key_list;
    std::vector<std::string>::iterator itr_chan;
    std::vector<std::string>::iterator itr_key;
    std::string response = "";
    bool allowedJoin = true;

    if (params.size() > 2) {
        return;
    }
    if (params.size() < 1)
    {
        client->addInServerReplies(ERR_NEEDMOREPARAMS(client->getNickname(), "JOIN"));
        return;
    }

    std::vector<std::string> chan_list = ft_split(params[0], ',');
    if(params.size() == 2)
    {
        key_list = ft_split(params[1], ',');
    }

    itr_key = key_list.begin();
    for (itr_chan = chan_list.begin(); itr_chan != chan_list.end(); ++itr_chan)
    {
        std::string chanName = *itr_chan;
        allowedJoin = true;  // Reset allowedJoin for each channel
        
        // Check for empty channel name or invalid format
        if (chanName.empty()) {
            client->addInServerReplies(ERR_NOSUCHCHANNEL(client->getNickname(), chanName));
            continue;
        }
        
        if (chanName.at(0) != '#' && chanName.at(0) != '&')
        {
            client->addInServerReplies(ERR_NOSUCHCHANNEL(client->getNickname(), chanName));
            continue;
        }
        
        if (isChannelInServer(chanName))
        {
            Channel &tempChannel = getChannel(chanName);  // Remove const to allow modifications
            // Client already in channel
            if(tempChannel.clientInChannel(client->getNickname()))
            {
                response = ERR_USERONCHANNEL(client->getUsername(), client->getNickname(), chanName);
                allowedJoin = false;
            }
            // Check limit mode (l)
            else if(tempChannel.getModeAtindex(4) && tempChannel.GetClientsNumber() >= tempChannel.GetLimit())
            {
                response = ERR_CHANNELISFULL(client->getNickname(), chanName);
                allowedJoin = false;
            }
            // Check invite-only mode (i)
            else if(tempChannel.getModeAtindex(0))
            {
                response = ERR_INVITEONLYCHAN(client->getNickname(), chanName);
                allowedJoin = false;
            }
            // Check key mode (k)
            else if (tempChannel.getModeAtindex(2))
            {
                std::stringstream ss;
                if (itr_key != key_list.end())
                {
                    ss << *itr_key;
                    int key;
                    ss >> key;
                    if (key != tempChannel.GetKey())
                    {
                        response = ERR_BADCHANNELKEY(client->getNickname(), chanName);
                        allowedJoin = false;
                    }
                    ++itr_key;
                }
                else
                {
                    response = ERR_BADCHANNELKEY(client->getNickname(), chanName);
                    allowedJoin = false;
                }
            }
            if (allowedJoin) 
            {
                response = RPL_JOIN(user_id(client->getNickname(), client->getUsername()), chanName);
                tempChannel.sendTo_all(response);
                tempChannel.add_client(*client);
                response = greetJoinedUser(*client, tempChannel);
            }
            client->addInServerReplies(response);
            continue;  // Use continue instead of break to process all channels
        }
        else
        {
            // Create new channel
            Channel newChannel;
            newChannel.SetName(chanName);
            newChannel.set_createiontime();
            
            // If key provided, set it
            if (itr_key != key_list.end())
            {
                std::stringstream ss;
                ss << *itr_key;
                int key;
                ss >> key;
                newChannel.SetKey(key);
                newChannel.setModeAtindex(2, true); // Set key mode
                ++itr_key;
            }
            
            response = RPL_JOIN(user_id(client->getNickname(), client->getUsername()), chanName);
            newChannel.add_admin(*client); // First user becomes admin
            channels.insert(make_pair(chanName, newChannel));
            response += greetJoinedUser(*client, getChannel(chanName));
            client->addInServerReplies(response);
        }
    }
}
