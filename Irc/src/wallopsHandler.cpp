#include "Server.hpp"

int         Server::wallopsHandler(const Msg&message, Client *client)
{
	std::string	check;

	client->setCurrentCommand("WALLOPS");
	if ((check = client->prefixCheck(message)) != "ok")
		return (this->*(this->replies[check]))(message, client);
	this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);

	broadcastMsg(message, client);
	return (CONNECT);
}
