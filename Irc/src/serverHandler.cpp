#include "Server.hpp"


void Server::settingClient(const Msg &message, Client *client)
{
    size_t parameterSize;

    parameterSize = message.getParameters().size();
	client->setStatus(SERVER);
	client->setInfo(SERVERNAME, message.getParameter(0));
	if (parameterSize == 4)
	{
		client->setInfo(TOKEN, message.getParameter(2));
		client->setInfo(SERVERINFO, message.getParameter(3));
	}
	else
	{
		client->setInfo(TOKEN, "0");
		client->setInfo(SERVERINFO, message.getParameter(2));
	}
}

int Server::serverHandler(const Msg &message, Client *client)
{
	client->setCurrentCommand("SERVER");
	if (client->getStatus() == UNKNOWN)
	{
		this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
		if (!client->getIsAuthorized() || (message.getParameters().size() < 3)
			|| (message.getParameter(0).find('.') == std::string::npos) || client->getInfo(NICK) != "" || client->getInfo(USERNAME) != "")
		{
			return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
		}
		if (this->sendClients.count(message.getParameter(0)) || this->serverName == message.getParameter((0)))
			return ((this->*(this->replies[ERR_ALREADYREGISTRED]))(message, client));
		settingClient(message, client);
		client->setInfo(UPLINKSERVER, this->serverName);
		client->setInfo(HOPCOUNT, std::string("1"));
		this->sendClients[message.getParameter(0)] = *client;
		this->serverRoll[message.getParameter(0)] = client;
		return ((this->*(this->replies[RPL_SERVER]))(message, client));
	}
	else if (client->getStatus() == SERVER)
	{
		this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
		if (message.getPrefix() == "")
			return (CONNECT);
		if (message.getParameters().size() <= 3)
			return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
		if (this->serverName == message.getParameter((0)) ||
			(this->sendClients.count(message.getParameter(0))))
		{

			return ((this->*(this->replies[ERR_ALREADYREGISTRED]))(message, client));
		}
		if (message.getParameter(1) == "1")
		{
			settingClient(message, client);
			client->setInfo(UPLINKSERVER, this->serverName);
			client->setInfo(HOPCOUNT, std::string("1"));
			this->sendClients[message.getParameter(0)] = *client;
			this->serverRoll[message.getParameter(0)] = client;
		}
		else
		{
			Client newClient(client->getFd());

			settingClient(message, &newClient);
			newClient.setInfo(UPLINKSERVER, message.getPrefix().substr(1, message.getPrefix().length()));
			newClient.setInfo(HOPCOUNT, message.getParameter(1));
			this->sendClients[message.getParameter(0)] = newClient;
		}
		(this->*(this->replies[RPL_SERVERBROADCAST]))(message, client);
	}
	else if (client->getStatus() == USER)
	{

	}
	return (CONNECT);
}



void Server::deleteSubServers(const std::string &targetServer, const std::string &info) {
    std::map<std::string, Client>::iterator it;
    std::map<std::string, Client>::iterator prev;
    bool                                    goToBegin;

    it = this->sendClients.begin();
    prev = this->sendClients.begin();
    goToBegin = false;
    while (it != this->sendClients.end())
    {
        if (it->second.getStatus() == USER)
        {
            if (it->second.getInfo(HOSTNAME) == targetServer)
            {
                goToBegin = true;
                this->sendClients.erase(it->first);
            }
        }
        else
        {
            if (it->second.getInfo(UPLINKSERVER) == targetServer)
            {
                goToBegin = true;
                deleteSubServers(it->second.getInfo(SERVERNAME), info);
            }
        }
        if (goToBegin)
        {
            it = this->sendClients.begin();
            goToBegin = false;
        }
        else
            ++it;
    }
    this->sendClients.erase(targetServer);
}

int Server::squitHandler(const Msg &message, Client *client)
{
	std::map<std::string, Client *>::iterator   it;
	std::string                                 from;

	client->setCurrentCommand("SQUIT");
	//if (message.getPrefix().empty() && (client->getInfo(MODE) != OPERATOR
	// || message.getParameter(0) == this->serverName))
	  //  return NO_PRIVILIGED
	if (message.getParameters().size() != 2)
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));

    if (message.getPrefix().empty())
        from = client->getInfo(NICK);
    else
        from = message.getPrefix().substr(1, message.getPrefix().length());
	if (message.getParameter(0) == this->serverName)
	{
		this->run = false;
		broadcastMsg(message, client);
		return (TOTALDISCONNECT);
	}
	else if (this->serverRoll.count(message.getParameter(0)))
    {
	    for (strClientPtrIter it = this->serverRoll.begin(); it != this->serverRoll.end(); ++it)
        {
            if (client->getInfo(SERVERNAME) != message.getParameter(0))
            {
                sendMsg(Msg(this->prefix
                                    , "WALLOPS"
                                    , "Received SQUIT "
                                    + message.getParameter(0)
                                    + " from " + from
                                    + " " + message.getParameter(1))
                                    , it->second);
            }
            if (it->second->getInfo(SERVERNAME) != client->getInfo(SERVERNAME))
            {
                sendMsg(Msg(":" + from
                                    , "SQUIT"
                                    , message.getParameter(0)
                                    + " " + message.getParameter(1))
                                    , it->second);
            }
        }
        return (DISCONNECT);
    }
    else if (this->sendClients.count(message.getParameter(0)))
    {

	    deleteSubServers(message.getParameter(0), message.getParameter(1));
	    broadcastMsg(Msg(":" + from
                                , "SQUIT"
                                , message.getParameter(0)
                                + " " + message.getParameter(1))
                                , client);
    }
    else
        return ((this->*(this->replies[ERR_NOSUCHSERVER]))(message, client));
    return (CONNECT);
}

int     Server::pingHandler(const Msg &message, Client *client)
{
    std::string					check;
    std::string					from;
    std::string                 target;
    std::vector<std::string>	*list;
    size_t						parameterSize;

    client->setCurrentCommand("PING");
    if (client->getStatus() == UNKNOWN)
        return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
    else if (client->getStatus() == USER)
        this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
    else
        this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
    if ((check = client->prefixCheck(message)) != "ok")
        return (this->*(this->replies[check]))(message, client);

    parameterSize = message.getParameters().size();
    if (parameterSize > 2)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
    else if (parameterSize == 0)
        return (this->*(this->replies[ERR_NOORIGIN]))(message, client);
    else if (parameterSize == 1)
    {
        if (message.getParameter(0)[0] == ':')
        {
            target = message.getParameter(0).substr(1, message.getParameter(0).length());
            list = getInfoFromWildcard(target);
        }
        else
        {
            sendMsg(Msg(this->prefix
                                , "PONG"
                                , this->serverName
                                + " :" + message.getParameter(0))
                                , client);
            return (CONNECT);
        }
    }
    else
    {
        if (message.getParameter(1)[0] == ':')
        {
            target = message.getParameter(1).substr(1, message.getParameter(1).length());
            list = getInfoFromWildcard(target);
        }
        else
        {
            target = message.getParameter(1);
            list = getInfoFromWildcard(target);
        }
    }
    if (!list)
    {
        delete list;
        return (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);
    }
    if (message.getPrefix().empty())
        from = client->getInfo(NICK);
    else
        from = message.getPrefix().substr(1, message.getPrefix().length());
    if (parameterSize == 1 || *(--list->end()) == this->serverName)
    {
        sendMsg(Msg(this->prefix
                            , "PONG"
                            , this->serverName + " " + from)
                            , &this->sendClients[from]);
    }
    else
    {
        sendMsg(Msg(':' + from
                            , "PING"
                            , message.getParameter(0) +
                            " :" + target)
                            , &this->sendClients[target]);
    }
    return (CONNECT);
}



int     Server::pongHandler(const Msg &message, Client *client)
{
    std::string     target;
    size_t          parameterSize;

    client->setCurrentCommand("PONG");
    parameterSize = message.getParameters().size();
    if (parameterSize == 0)
        return (this->*(this->replies[ERR_NOORIGIN]))(message, client);
    if (parameterSize != 1)
    {
        if (message.getParameter(1)[0] == ':')
            target = message.getParameter(1).substr(1, message.getParameter(1).length());
        else
            target = message.getParameter(1);
    }
    if (message.getParameters().size() == 1 || target == this->serverName)
    {
        client->setWaitPong(true);
        client->setLastPing(std::time(NULL));
        client->setPingRAnge(std::time(NULL));
    }
    else if (this->sendClients.count(target))
        sendMsg(message, &this->sendClients[target]);
    return (CONNECT);
}