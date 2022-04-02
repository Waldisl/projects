#include "Server.hpp"


std::string     getTextMsg(const Msg &message)
{
    std::string textMsg;

    textMsg += message.getParameter(0);
    
    if (message.getParameter(1).at(0) == ':')
    {
        for (int i = 1; i < int(message.getParameters().size()); i++)
            textMsg += (" " + message.getParameter(i));
    }
    else
        textMsg += (" :" + message.getParameter(1));
    return (textMsg);
}

std::string     Server::getClientPrefix(Client *client)
{
	std::string returnString;

	returnString += client->getInfo(NICK);
	returnString += std::string("!~");
	returnString += client->getInfo(USERNAME);
	returnString += std::string("@");
	returnString += client->getInfo(HOSTNAME);
	return (returnString);
}

int     Server::privmsgHandler(const Msg &message, Client *client)
{
    Client                  *sender;
    Client                  *targetClient;
    Channel                 *targetChannel;
    std::vector<Client *>   joinedUsers;

    client->setCurrentCommand("PRIVMSG");
    
    if (message.getParameters().size() == 0)
        return ((this->*(this->replies[ERR_NORECIPIENT]))(message, client));
    else if (message.getParameters().size() == 1)
        return ((this->*(this->replies[ERR_NOTEXTTOSEND]))(message, client));
    else if (message.getParameters().size() > 2 && message.getParameter(1).at(0) != ':')
        return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
    else
    {   

        if (message.getParameter(0).at(0) == '#' || message.getParameter(0).at(0) == '&')
        {   
            if (this->localChannelRoll.find(message.getParameter(0)) != this->localChannelRoll.end())
                targetChannel = &this->localChannelRoll[message.getParameter(0)];
            else if (this->remoteChannelRoll.find(message.getParameter(0)) != this->remoteChannelRoll.end())
                targetChannel = &this->remoteChannelRoll[message.getParameter(0)];
            else    // 401
                return ((this->*(this->replies[ERR_NOSUCHNICK]))(message, client));

            if (client->getStatus() == USER)
                sender = client;
            else
                sender = &this->sendClients[message.getPrefix().substr(1)];


            joinedUsers = targetChannel->getUsersRoll(this->serverName);
            for (int i = 0; i < (int)joinedUsers.size(); i++)
                this->sendMsg(Msg(":" + getClientPrefix(sender), "PRIVMSG", getTextMsg(message)), joinedUsers[i]);


            this->broadcastMsg(Msg(":" + sender->getInfo(NICK), "PRIVMSG", getTextMsg(message)), client);
        }
        else
        {
            if ((this->clientRoll.size() != 0) && (this->clientRoll.find(message.getParameter(0)) != this->clientRoll.end()))
            {       
                targetClient = this->clientRoll[message.getParameter(0)];
                if (message.getPrefix().empty())
                    this->sendMsg(Msg(":" + getClientPrefix(client), "PRIVMSG", getTextMsg(message)), targetClient);
                else
                    this->sendMsg(Msg(message.getPrefix(), "PRIVMSG", getTextMsg(message)), targetClient);
            }
            else if (this->sendClients.find(message.getParameter(0)) != this->sendClients.end())
            {
                targetClient = &this->sendClients[message.getParameter(0)];
                if (message.getPrefix().empty())
                    this->sendMsg(Msg(":" + getClientPrefix(client), "PRIVMSG", getTextMsg(message)), targetClient);
                else
                    this->sendMsg(Msg(message.getPrefix(), "PRIVMSG", getTextMsg(message)), targetClient);
            }
            else
                return ((this->*(this->replies[ERR_NOSUCHNICK]))(message, client));
            }
    }
    return (CONNECT);
}


int     Server::noticeHandler(const Msg &message, Client *client)
{
	Client                  *sender;
	Client                  *targetClient;
	Channel                 *targetChannel;
	std::vector<Client *>   joinedUsers;

	client->setCurrentCommand("NOTICE");

	if (message.getParameters().size() == 0)
		return ((this->*(this->replies[ERR_NORECIPIENT]))(message, client));
	else if (message.getParameters().size() == 1)
		return ((this->*(this->replies[ERR_NOTEXTTOSEND]))(message, client));
	else if (message.getParameters().size() > 2 && message.getParameter(1).at(0) != ':')
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
	else
	{

		if (message.getParameter(0).at(0) == '#' || message.getParameter(0).at(0) == '&')
		{
			if (this->localChannelRoll.find(message.getParameter(0)) != this->localChannelRoll.end())
				targetChannel = &this->localChannelRoll[message.getParameter(0)];
			else if (this->remoteChannelRoll.find(message.getParameter(0)) != this->remoteChannelRoll.end())
				targetChannel = &this->remoteChannelRoll[message.getParameter(0)];
			else    // 401
				return ((this->*(this->replies[ERR_NOSUCHNICK]))(message, client));

			if (client->getStatus() == USER)
				sender = client;
			else
				sender = &this->sendClients[message.getPrefix().substr(1)];


			joinedUsers = targetChannel->getUsersRoll(this->serverName);
			for (int i = 0; i < (int)joinedUsers.size(); i++)
				this->sendMsg(Msg(":" + getClientPrefix(sender), "NOTICE", getTextMsg(message)), joinedUsers[i]);


			this->broadcastMsg(Msg(":" + sender->getInfo(NICK), "NOTICE", getTextMsg(message)), client);
		}
		else
		{
			if ((this->clientRoll.size() != 0) && (this->clientRoll.find(message.getParameter(0)) != this->clientRoll.end()))
			{
				targetClient = this->clientRoll[message.getParameter(0)];
				if (message.getPrefix().empty())
					this->sendMsg(Msg(":" + getClientPrefix(client), "NOTICE", getTextMsg(message)), targetClient);
				else
					this->sendMsg(Msg(message.getPrefix(), "NOTICE", getTextMsg(message)), targetClient);
			}
			else if (this->sendClients.find(message.getParameter(0)) != this->sendClients.end())
			{
				targetClient = &this->sendClients[message.getParameter(0)];
				if (message.getPrefix().empty())
					this->sendMsg(Msg(":" + getClientPrefix(client), "NOTICE", getTextMsg(message)), targetClient);
				else
					this->sendMsg(Msg(message.getPrefix(), "NOTICE", getTextMsg(message)), targetClient);
			}
			else
				return ((this->*(this->replies[ERR_NOSUCHNICK]))(message, client));
		}
	}
	return (CONNECT);
}
