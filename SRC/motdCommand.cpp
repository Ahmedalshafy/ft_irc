#include "../Includes/Server.hpp"

void	Server::motdCommand(Client *client)
{
    std::ostringstream oss;
    std::string line;
    std::ifstream infile;

	if(!client->getIsRegistered())
		return;
    infile.open("./source_files/motd.txt", std::ios::in);
	
	client->getServerReplies().push_back( RPL_MOTDSTART(client->getUsername(),std::string("ircserver")));
	client->getServerReplies().push_back( RPL_WELCOME(user_id(client->getNickname(),client->getUsername()),client->getNickname()));
	client->getServerReplies().push_back( RPL_YOURHOST(client->getUsername(),"irssi", "1"));
	client->getServerReplies().push_back( RPL_CREATED(client->getUsername(), std::string("creation_date")));
	client->getServerReplies().push_back( RPL_MYINFO(client->getUsername(),"irssi", "1", "","",""));
	client->getServerReplies().push_back( RPL_ISUPPORT(client->getUsername(),"CHANMODES=ikolt"));
    if (infile.is_open())
    {
        while (std::getline(infile,line))
        {
            client->getServerReplies().push_back( RPL_MOTD(std::string("ircserver"),line));
        }
        infile.close();
    }
    else
        client->getServerReplies().push_back( ERR_NOMOTD(std::string("ircserver")));
		
    client->getServerReplies().push_back( RPL_ENDOFMOTD(std::string("ircserver")));
    return ;
}
