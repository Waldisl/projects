#include "Server.hpp"



Client		*Server::hasTarget(const std::string &target, strClientPtrIter start, strClientPtrIter end)
{
    for (; start != end; ++start)
    {
        if (target == start->second->getInfo(SERVERNAME))
            return (start->second);
    }
    return (NULL);
}

void		Server::incrLocalByte(Client *client, const Msg &message)
{
    this->infosPerCommand[client->getCurrentCommand()].incrBytes(message.getTotalMsg().length());
}

void		Server::incrRemoteByte(Client *client, const Msg &message)
{
    this->infosPerCommand[client->getCurrentCommand()].incrBytes(message.getTotalMsg().length());
}

std::vector<std::string> *Server::getInfoFromWildcard(const std::string &info)
{
    std::vector<std::string> *ret = new std::vector<std::string>;
    strClientIter it;

    ret->reserve(10);
    for (it = this->sendClients.begin(); it != this->sendClients.end(); ++it)
    {
        if (it->second.getStatus() == SERVER && match(info.c_str(), it->second.getInfo(SERVERNAME).c_str()))
            ret->push_back(it->second.getInfo(SERVERNAME));
    }
    if (match(info.c_str(), this->serverName.c_str()))
        ret->push_back(this->serverName);
    if (ret->empty())
    {
        delete ret;
        return (NULL);
    }
    return (ret);
}



int Server::versionHandler(const Msg &message, Client *client)
{
    std::vector<std::string>	*list;
    std::string					check;
    std::string					toClient;
    size_t						parameterSize;

    client->setCurrentCommand("VERSION");
    if (client->getStatus() == UNKNOWN)
        return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
    else if (client->getStatus() == USER)
        this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
    else
        this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);

    if ((check = client->prefixCheck(message)) != "ok")
        return (this->*(this->replies[check]))(message, client);

    parameterSize = message.getParameters().size();
    if (parameterSize > 1)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
    else if (parameterSize == 1)
        list = getInfoFromWildcard(message.getParameter(0));
    else
        list = getInfoFromWildcard(this->serverName);
    if (!list)
    {
        delete list;
        return (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);
    }

    if (message.getPrefix().empty())
        toClient = client->getInfo(NICK);
    else
        toClient = message.getPrefix().substr(1, message.getPrefix().length());
    if (*(--list->end()) == this->serverName)
    {
        sendMsg(Msg(this->prefix
                , RPL_VERSION
                , toClient
                  + " " + this->version
                  + ". " + this->serverName)
                , client);
        list->pop_back();
    }
    else
    {
        sendMsg(Msg(":" + toClient
                , "VERSION"
                , *(--list->end()))
                , &this->sendClients[*(--list->end())]);
    }
    delete list;
    return (CONNECT);
}


int			Server::statsHandler(const Msg &message, Client *client)
{
    std::vector<std::string>	*list;
    std::string					check;
    std::string					from;
    size_t						parameterSize;
    std::map<std::string, int (Server::*)(const Msg &, Client *)>::iterator	query;

    client->setCurrentCommand("STATS");
    if (client->getStatus() == UNKNOWN)
        return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
    else if (client->getStatus() == USER)
        this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
    else
        this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);

    if ((check = client->prefixCheck(message)) != "ok")
        return (this->*(this->replies[check]))(message, client);


    parameterSize = message.getParameters().size();
    if (parameterSize == 0)
        return (this->*(this->replies[RPL_ENDOFSTATS]))(message, client);
    else if ((query = this->replies.find(std::string("STATS_") + message.getParameter(0)[0])) == this->replies.end())
        return (this->*(this->replies[RPL_ENDOFSTATS]))(message, client);
    else if (parameterSize > 2)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
    else if (parameterSize == 2)
        list = getInfoFromWildcard(message.getParameter(1));
    else
        list = getInfoFromWildcard(this->serverName);

    if (!list)
    {
        delete list;
        return (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);
    }

    if (*(--list->end()) == this->serverName)
    {
        (this->*(query->second))(message, client);
        //(this->*(this->replies[std::string("STATS_") + message.getParameter(0)[0]]))(message, client);
        (this->*(this->replies[RPL_ENDOFSTATS]))(message, client);
    }
    else
    {
        if (message.getPrefix().empty())
            from = ":" + client->getInfo(NICK);
        else
            from = message.getPrefix();
        sendMsg(Msg(from
                , "STATS"
                , message.getParameter(0)
                  + " " + *(--list->end()))
                , &this->sendClients[*(--list->end())]);
    }
    delete list;
    return (CONNECT);
}

int			Server::linksHandler(const Msg &message, Client *client)
{
    std::string					check;
    std::string					parameter;
    std::vector<std::string>	*list;
    size_t						parameterSize;

    client->setCurrentCommand("LINKS");
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
    else if (parameterSize == 2)
        list = getInfoFromWildcard(message.getParameter(1));
    else if (parameterSize == 1)
        list = getInfoFromWildcard(message.getParameter(0));
    else
        list = getInfoFromWildcard("*");
    if (!list)
    {
        delete list;
        return (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);
    }

    for (std::vector<std::string>::iterator it = list->begin(); it != list->end(); ++it)
    {
        if (message.getPrefix().empty())
            parameter = client->getInfo(NICK);
        else
            parameter = message.getPrefix().substr(1, message.getPrefix().length());
        if (*it == this->serverName)
        {
            sendMsg(Msg(this->prefix
                    , RPL_LINKS
                    , parameter
                      + " " + this->serverName
                      + " " + this->serverName
                      + " :0 " + this->info)
                    , client);
        }
        else
        {
            sendMsg(Msg(this->prefix
                    , RPL_LINKS
                    , parameter
                      + " " + this->sendClients[*it].getInfo(SERVERNAME)
                      + " " + this->sendClients[*it].getInfo(UPLINKSERVER)
                      + " :" + this->sendClients[*it].getInfo(HOPCOUNT)
                      + " " + this->sendClients[*it].getInfo(SERVERINFO))
                    , client);
        }
    }
    (this->*(this->replies[RPL_ENDOFLINKS]))(message, client);
    delete list;
    return (CONNECT);
}

int			Server::timeHandler(const Msg &message, Client *client)
{
    std::string					check;
    std::string					toClient;
    std::vector<std::string>	*list;
    time_t						now;
    size_t						parameterSize;

    client->setCurrentCommand("TIME");
    if (client->getStatus() == UNKNOWN)
        return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
    else if (client->getStatus() == USER)
        this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
    else
        this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
    if ((check = client->prefixCheck(message)) != "ok")
        return (this->*(this->replies[check]))(message, client);

    now = time(NULL);
    parameterSize = message.getParameters().size();
    if (parameterSize > 1)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
    else if (parameterSize == 1)
        list = getInfoFromWildcard(message.getParameter(0));
    else
        list = getInfoFromWildcard(this->serverName);
    if (!list)
    {
        delete list;
        (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);
    }

    if (message.getPrefix().empty())
        toClient = client->getInfo(NICK);
    else
        toClient = message.getPrefix().substr(1, message.getPrefix().length());
    if (*(--list->end()) == this->serverName)
    {
        sendMsg(Msg(this->prefix
                , RPL_TIME
                , toClient
                  + " :" + getTimestamp(now, false))
                , client);
    }
    else
    {
        sendMsg(Msg(":" + toClient
                , "TIME"
                , *(--list->end()))
                , &this->sendClients[*(--list->end())]);
    }
    delete list;
    return (CONNECT);
}



int				Server::connectHandler(const Msg &message, Client *client)
{
    std::string check;
    std::string from;
    size_t		parameterSize;

    client->setCurrentCommand("CONNECT");
    if (client->getStatus() == UNKNOWN)
        return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
    else if (client->getStatus() == USER)
        this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
    else
        this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
    if ((check = client->prefixCheck(message)) != "ok")
        return (this->*(this->replies[check]))(message, client);

    parameterSize = message.getParameters().size();
    if (parameterSize == 0 || parameterSize == 2)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
    if (!isActualAddress(message.getParameter(0)))
        return (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);

    if (message.getPrefix().empty())
        from = client->getInfo(NICK);
    else
        from = message.getPrefix().substr(1, message.getPrefix().length());
    if (parameterSize == 1 || message.getParameter(2) == this->serverName)
    {
        broadcastMsg(Msg(this->prefix
                , "WALLOPS"
                , ":Received CONNECT "
                  + message.getParameter(0)
                  + " from " + from)
                , client);
        if (message.getParameters().size() == 1)
            this->connectServer(message.getParameter(0));
    }
    else
    {
        sendMsg(Msg(":" + from
                , "CONNECT"
                , message.getParameter(0)
                  + " " + message.getParameter(1)
                  + " " + message.getParameter(2))
                , &this->sendClients[message.getParameter(2)]);
    }
    return (CONNECT);
}

int				Server::traceHandler(const Msg &message, Client *client)
{
    std::string					check;
    std::string					from;
    std::vector<std::string>	*list;
    size_t						parameterSize;
    strClientPtrIter			found;
    Client						*target;

    client->setCurrentCommand("TRACE");
    if (client->getStatus() == UNKNOWN)
        return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
    else if (client->getStatus() == USER)
        this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
    else
        this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
    if ((check = client->prefixCheck(message)) != "ok")
        return (this->*(this->replies[check]))(message, client);

    parameterSize = message.getParameters().size();
    if (parameterSize > 1)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
    else if (parameterSize == 1)
        list = getInfoFromWildcard(message.getParameter(0));
    else
        list = getInfoFromWildcard(this->serverName);
    if (!list)
    {
        delete list;
        return (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);
    }
    if (message.getPrefix().empty())
        from = client->getInfo(NICK);
    else
        from = message.getPrefix().substr(1, message.getPrefix().length());
    found = this->clientRoll.find(*(--list->end()));
    target = &this->sendClients[from];
    if (*(--list->end()) == this->serverName || found != this->clientRoll.end())
    {

        for (strClientPtrIter it = this->serverRoll.begin(); it != this->serverRoll.end(); ++it)
        {
            sendMsg(Msg(this->prefix
                    , RPL_TRACESERVER
                    , from + " Serv 1 0S 0C "
                      + it->second->getInfo(SERVERNAME)
                      + " *|*@" + this->serverName
                      + " :V")
                    , target);
        }
        sendMsg(Msg(this->prefix
                , RPL_TRACEEND
                , from + " " + this->serverName
                  + " " + this->version + " :End of TRACE")
                , target);
    }
    else
    {
        sendMsg(Msg(this->prefix
                , RPL_TRACELINK
                , from + " Link "
                  + this->version + " " + *(--list->end())
                  + " " + this->serverName + " V"
                  + " " + getTimestamp(std::time(NULL) - this->startTime, true)
                  + " 0 0")
                , target);
        sendMsg(Msg(":" + from
                , "TRACE"
                , *(--list->end()))
                , &this->sendClients[*(--list->end())]);
    }
    return (CONNECT);
}

int     Server::adminHandler(const Msg &message, Client *client)
{
    std::string					check;
    std::string					from;
    std::vector<std::string>	*list;
    size_t						parameterSize;
    strClientPtrIter			found;
    Client						*target;

    client->setCurrentCommand("ADMIN");
    if (client->getStatus() == UNKNOWN)
        return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
    else if (client->getStatus() == USER)
        this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
    else
        this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
    if ((check = client->prefixCheck(message)) != "ok")
        return (this->*(this->replies[check]))(message, client);

    parameterSize = message.getParameters().size();
    if (parameterSize > 1)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
    else if (parameterSize == 1)
        list = getInfoFromWildcard(message.getParameter(0));
    else
        list = getInfoFromWildcard(this->serverName);
    if (!list)
    {
        delete list;
        return (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);
    }
    if (message.getPrefix().empty())
        from = client->getInfo(NICK);
    else
        from = message.getPrefix().substr(1, message.getPrefix().length());
    found = this->clientRoll.find(*(--list->end()));
    target = &this->sendClients[from];
    if (*(--list->end()) == this->serverName || found != this->clientRoll.end())
    {

        sendMsg(Msg(this->prefix
                , RPL_ADMINME
                , from + " " + *(--list->end())
                + " :Administrative info")
                , target);
        sendMsg(Msg(this->prefix
                    , RPL_ADMINLOC1
                    , from + " :" + this->adminLoc1)
                    , target);
        sendMsg(Msg(this->prefix
                    , RPL_ADMINLOC2
                    , from + " :" + this->adminLoc2)
                    , target);
        sendMsg(Msg(this->prefix
                    , RPL_ADMINEMAIL
                    , from + " :" + this->adminEmail)
                    , target);
    }
    else
    {
        sendMsg(Msg(":" + from
                    , "ADMIN"
                    , *(--list->end()))
                    , &this->sendClients[*(--list->end())]);
    }
    return (CONNECT);
}

int     Server::infoHandler(const Msg &message, Client *client)
{
    std::string					check;
    std::string					from;
    std::vector<std::string>	*list;
    size_t						parameterSize;
    strClientPtrIter			found;
    Client						*target;

    client->setCurrentCommand("INFO");
    if (client->getStatus() == UNKNOWN)
        return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
    else if (client->getStatus() == USER)
        this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
    else
        this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
    if ((check = client->prefixCheck(message)) != "ok")
        return (this->*(this->replies[check]))(message, client);

    parameterSize = message.getParameters().size();
    if (parameterSize > 1)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
    else if (parameterSize == 1)
        list = getInfoFromWildcard(message.getParameter(0));
    else
        list = getInfoFromWildcard(this->serverName);
    if (!list)
    {
        delete list;
        return (this->*(this->replies[ERR_NOSUCHSERVER]))(message, client);
    }
    if (message.getPrefix().empty())
        from = client->getInfo(NICK);
    else
        from = message.getPrefix().substr(1, message.getPrefix().length());
    found = this->clientRoll.find(*(--list->end()));
    target = &this->sendClients[from];
    if (*(--list->end()) == this->serverName || found != this->clientRoll.end())
    {
        sendMsg(Msg(this->prefix
                , RPL_INFO
                , from
                  + " :" + this->version)
                , target);
        sendMsg(Msg(this->prefix
                , RPL_INFO
                , from + " :Birth Data: "
                + getTimestamp(this->startTime, false))
                , target);
        sendMsg(Msg(this->prefix
                , RPL_INFO
                , from + " :Uptime: "
                + getTimestamp(std::time(NULL) - this->startTime, true))
                , target);
        sendMsg(Msg(this->prefix
                , RPL_ENDOFINFO
                , from + " :End of INFO list")
                , target);
    }
    else
    {
        sendMsg(Msg(":" + from
                , "INFO"
                , *(--list->end()))
                , &this->sendClients[*(--list->end())]);
    }
    return (CONNECT);
}