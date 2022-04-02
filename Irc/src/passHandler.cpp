#include "Server.hpp"

int					Server::passHandler(const Msg &message, Client *client)
{
	client->setCurrentCommand("PASS");
	if (message.getParameters().empty())
		this->sendMsg(Msg(this->prefix, ERR_NEEDMOREPARAMS, " :Not enough parameters"), client);
	else if (client->getIsAuthorized())
		this->sendMsg(Msg(this->prefix, ERR_ALREADYREGISTRED, " :You already reregistered"), client);
	else if (this->pass == message.getParameter(0))
		client->setIsAuthorized(true);
	if (client->getStatus() == USER)
		this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
	else if (client->getStatus() == SERVER)
		this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
	return (CONNECT);
}
