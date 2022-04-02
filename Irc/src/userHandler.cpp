#include "Server.hpp"

static bool			isActualNickName(const Msg &message)
{
	for (size_t i = 0; i < message.getParameter(0).length(); i++)
	{
		if (i == 0 && !isInTheMask(std::string(LETTER) + std::string(SPECIAL), message.getParameter(0)[i]))
			return false;
		else if (!isInTheMask(std::string(LETTER) + std::string(SPECIAL) + std::string(DIGIT), message.getParameter(0)[i]))
			return false;
	}
	return true;
}

static bool			isVaildUserName(const Msg &message)
{
	for (size_t i = 0; i < message.getParameter(0).length(); i++)
	{
		if (isInTheMask(std::string(USER_FORMAT), message.getParameter(0)[i]))
			return false;
	}
	return true;
}

static bool			isActualUserMode(const std::string &string)
{
	for (size_t i = 0; i < string.length(); i++)
	{
		if (i != 0 && !isInTheMask(std::string(MODEUSER), string[i]))
			return (false);
		else if (!isInTheMask(std::string(MODEUSER) + std::string("+-"), string[i]))
			return (false);
	}
	return (true);
}

static bool			isActualHopCountToken(const std::string &string)
{
	for (size_t i = 0; i < string.length(); i++)
	{
		if (!isInTheMask(std::string(DIGIT), string[i]))
			return (false);
	}
	return (true);
}

static Msg		setNickMsg(const Msg &message)
{
	std::string			parameters;
	Msg				returnMsg;

	parameters = message.getParameter(0).substr(1, message.getParameter(0).length());
	parameters += std::string(" :1");
	returnMsg = Msg(std::string(""), RPL_NICK, parameters);
	return (returnMsg);
}

static Msg		setUserMsg(const Msg &message, std::string serverName)
{
	std::string		parameters;
	Msg			returnMsg;

	parameters = message.getParameter(2);
	parameters += std::string(" ");
	parameters += message.getParameter(3);
	parameters += std::string(" ");
	parameters += serverName;
	parameters += std::string(" ");
	parameters += message.getParameter(6);
	returnMsg = Msg(std::string(""), RPL_USER, parameters);
	return (returnMsg);
}

static bool			checkMsg(const Msg &message)
{
	if (!isActualHopCountToken(message.getParameter(4)) || ft_atoi(message.getParameter(4).c_str()) != 1)
		return (false);
	if (message.getParameter(5)[0] == '-')
		return (false);
	if (!isActualUserMode(message.getParameter(5)))
		return (false);
	return (true);
}

static int			setNick(Client *client, const Msg &message, bool isServer,
					std::map<std::string, Client> &sendClients,
					std::map<std::string, Client *> &clientRoll)
{
	if (client->getInfo(NICK) != "")
	{
		sendClients.erase(client->getInfo(NICK));
		if (!isServer)
			clientRoll.erase(client->getInfo(NICK));
	}
	client->setInfo(NICK, message.getParameter(0));
	sendClients[message.getParameter(0)] = *client;
	if (!isServer)
		clientRoll[message.getParameter(0)] = &sendClients[message.getParameter(0)];
	return (CONNECT);
}

static void			setUser(const Msg &message, Client *client, std::string address,
					std::map<std::string, Client> &sendClients, std::string serverName)
{
	std::string		realName;
	std::string		userName;

	userName = (message.getParameter(0)[0] == '~' ?
	message.getParameter(0).substr(1, message.getParameter(0).length())
	: message.getParameter(0));
	realName = (message.getParameter(3)[0] == ':' ?
	message.getParameter(3).substr(1, message.getParameter(3).length())
	: message.getParameter(3));
	client->setInfo(USERNAME, userName);
	client->setInfo(UPLINKSERVER, serverName);
	client->setInfo(ADDRESS, address);
	client->setInfo(REALNAME, realName);
	if (client->getInfo(NICK) != "")
	{
		(sendClients[client->getInfo(NICK)]).setInfo(USERNAME, userName);
		(sendClients[client->getInfo(NICK)]).setInfo(UPLINKSERVER, serverName);
		(sendClients[client->getInfo(NICK)]).setInfo(ADDRESS, address);
		(sendClients[client->getInfo(NICK)]).setInfo(REALNAME, realName);
	}
}

static std::string	removeMode(const std::string &mode, const char key)
{
	std::string returnString;

	for (size_t i = 0; i < mode.length(); ++i)
	{
		if (mode[i] != key)
			returnString += mode[i];
	}
	return (returnString);
}

static void			setMode(const std::string &mode, Client *client,
					std::map<std::string, Client> &sendClients)
{
	size_t	i;
	bool	isSetMode;

	i = 0;
	isSetMode = true;
	if (mode[i] == '-')
		isSetMode = false;
	if (mode[i] == '+' || mode[i] == '-')
		++i;
	while (i < mode.length())
	{
		if (isSetMode && client->getInfo(USERMODE).find(mode[i]) == std::string::npos)
			client->setInfo(USERMODE, client->getInfo(USERMODE) + mode[i]);
		if (!isSetMode && client->getInfo(USERMODE).find(mode[i]) != std::string::npos)
			client->setInfo(USERMODE, removeMode(client->getInfo(USERMODE), mode[i]));
		++i;
	}
	sendClients[client->getInfo(NICK)].setInfo(USERMODE, client->getInfo(USERMODE));
}

int					Server::setLocalNick(const Msg &message, Client *client)
{
	if (message.getParameters().empty())
		return ((this->*(this->replies[ERR_NONICKNAMEGIVEN]))(message, client));
	if (1 != message.getParameters().size())
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
	if (!isActualNickName(message) || 9 < message.getParameter(0).length())
		return ((this->*(this->replies[ERR_ERRONEUSNICKNAME]))(message, client));
	if (!client->getIsAuthorized())
		return ((this->*(this->replies[ERR_PASSUNAUTHORIE]))(message, client));
	if (this->sendClients.count(message.getParameter(0))
	|| this->serverName == message.getParameter(0))
		return ((this->*(this->replies[ERR_NICKNAMEINUSE]))(message, client));
	setNick(client, message, false, this->sendClients, this->clientRoll);
	if (client->getInfo(USERNAME) == "")
		return (CONNECT);
	(this->*(this->replies[RPL_REGISTERUSER]))(message, client);
	return ((this->*(this->replies[RPL_WELCOMEMESSAGE]))(message, client));
}

int					Server::resetLocalNick(const Msg &message, Client *client)
{
	if (message.getPrefix() != ""
	&& message.getPrefix() != std::string(":") + client->getInfo(SERVERNAME))
		return ((this->*(this->replies[ERR_PREFIX]))(message, client));
	if (message.getParameters().size() != 1)
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
	if (!isActualNickName(message) || 9 < message.getParameter(0).length())
		return ((this->*(this->replies[ERR_ERRONEUSNICKNAME]))(message, client));
	if (this->sendClients.count(message.getParameter(0))
	|| this->serverName == message.getParameter(0))
		return ((this->*(this->replies[ERR_NICKNAMEINUSE]))(message, client));
	(this->*(this->replies[RPL_NICK]))(message, client);
	(this->*(this->replies[RPL_NICKBROADCAST]))(message, client);
	return (setNick(client, message, false, this->sendClients, this->clientRoll));
}

int					Server::localNickHandler(const Msg &message, Client *client)
{
	if (client->getStatus() == UNKNOWN)
		return (this->setLocalNick(message, client));
	else if (client->getStatus() == USER)
		return (this->resetLocalNick(message, client));
	return (CONNECT);
}

int					Server::setRemoteNick(const Msg &message, Client *client)
{
	Client	remoteUser(client->getFd(),true);
	Msg	userMsg;

	if (message.getParameters().size() != 2 && message.getParameters().size() != 7)
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
	if (!isActualNickName(message) || 9 < message.getParameter(0).length())
		return ((this->*(this->replies[ERR_ERRONEUSNICKNAME]))(message, client));
	if (this->sendClients.count(message.getParameter(0))
	|| this->serverName == message.getParameter(0))
		(this->*(this->replies[RPL_KILL]))(message, client);
	if (this->clientRoll.count(message.getParameter(0)))
		return ((this->*(this->replies[ERR_NICKCOLLISION]))(message, this->clientRoll[message.getParameter(0)]));
	if (this->sendClients.count(message.getParameter(0))
	&& this->sendClients[message.getParameter(0)].getStatus() == USER)
	{
		this->sendClients.erase(message.getParameter(0));
		return (CONNECT);
	}
	if ((this->sendClients.count(message.getParameter(0)) && this->sendClients[message.getParameter(0)].getStatus() == SERVER)
	|| this->serverName == message.getParameter(0))
		return ((this->*(this->replies[ERR_CANTKILLSERVER]))(message, client));
	if (message.getParameters().size() == 7 && !checkMsg(message))
		return (CONNECT);
	setNick(&remoteUser, message, true, this->sendClients, this->clientRoll);
	if (message.getParameters().size() == 7)
	{
		userMsg = setUserMsg(message, client->getInfo(SERVERNAME));
		setUser(userMsg, &remoteUser, userMsg.getParameter(1), this->sendClients, userMsg.getParameter(2));
		setMode(message.getParameter(5), &remoteUser, this->sendClients);
		return (this->*(this->replies[RPL_REGISTERUSER]))(message, &remoteUser);
	}
	return (CONNECT);
}

int					Server::resetRemoteNick(const Msg &message, Client *client)
{
	std::string			prefix;
	Msg				formatedMsg;
	Client				remoteUser;

	prefix = message.getPrefix().substr(1, message.getPrefix().length());
	if (this->sendClients[prefix].getStatus() != UNKNOWN
	&& this->sendClients[prefix].getStatus() != USER)
		return ((this->*(this->replies[ERR_PREFIX]))(message, client));
	if (message.getParameters().size() != 1)
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
	if (message.getParameter(0)[0] != ':')
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
	formatedMsg = setNickMsg(message);
	remoteUser = this->sendClients[prefix];
	if (!isActualNickName(formatedMsg) || 9 < formatedMsg.getParameter(0).length())
		return ((this->*(this->replies[ERR_ERRONEUSNICKNAME]))(formatedMsg, client));
	if (this->sendClients.count(formatedMsg.getParameter(0))
	|| this->serverName == formatedMsg.getParameter(0))
		return ((this->*(this->replies[ERR_NICKNAMEINUSE]))(formatedMsg, &this->sendClients[prefix]));
	if (remoteUser.getStatus() == USER)
		(this->*(this->replies[RPL_NICKBROADCAST]))(formatedMsg, &remoteUser);
	setNick(&remoteUser, formatedMsg, true, this->sendClients, this->clientRoll);
	return (CONNECT);
}

int					Server::remoteNickHandler(const Msg &message, Client *client)
{
	std::string	prefix;

	if (message.getPrefix() == "")
		return (this->setRemoteNick(message, client));
	prefix = message.getPrefix().substr(1, message.getPrefix().length());
	if (this->getParentServer(prefix) == client->getInfo(NICK))
		return (this->setRemoteNick(message, client));
	if (this->sendClients.count(prefix) && !this->clientRoll.count(prefix)
	&& !this->serverRoll.count(prefix))
		return (this->resetRemoteNick(message, client));
	return ((this->*(this->replies[ERR_PREFIX]))(message, client));
}

int					Server::nickHandler(const Msg &message, Client *client)
{
	client->setCurrentCommand("NICK");
	if (client->getStatus() == SERVER)
	{
		this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
		return (this->remoteNickHandler(message, client));
	}
	this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
	return (this->localNickHandler(message, client));
}

int					Server::setLocalUser(const Msg &message, Client *client)
{
	if (client->getStatus() == UNKNOWN)
	{
		if (message.getParameters().size() != 4)
			return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
		if (!client->getIsAuthorized())
			return ((this->*(this->replies[ERR_PASSUNAUTHORIE]))(message, client));
		if (client->getInfo(USERNAME) != "")
			return ((this->*(this->replies[ERR_ALREADYREGISTRED]))(message, client));
		if (!isVaildUserName(message))
			return ((this->*(this->replies[ERR_ERRONEUSUSERNAME]))(message, client));
		setUser(message, client, this->ipAddress, this->sendClients, this->serverName);
		if (client->getInfo(NICK) == "")
			return (CONNECT);

		(this->*(this->replies[RPL_REGISTERUSER]))(message, client);
		return ((this->*(this->replies[RPL_WELCOMEMESSAGE]))(message, client));
	}
	else if (client->getStatus() == USER)
	{
		if (!message.getPrefix().empty()
		&& message.getPrefix() != std::string(":") + client->getInfo(NICK))
			return ((this->*(this->replies[ERR_PREFIX]))(message, client));
		return ((this->*(this->replies[ERR_ALREADYREGISTRED]))(message, client));
	}
	return (CONNECT);
}

int					Server::setRemoteUser(const Msg &message, Client *client)
{
	std::string							prefix;
	std::list<std::string>::iterator	iterator;
	std::list<std::string>				serverRoll;

	if (message.getPrefix().empty())
		return ((this->*(this->replies[ERR_PREFIX]))(message, client));
	prefix = message.getPrefix().substr(1, message.getPrefix().length());
	if (!this->sendClients.count(prefix) || this->clientRoll.count(prefix)
	|| this->serverRoll.count(prefix))
		return ((this->*(this->replies[ERR_PREFIX]))(message, client));
	if (this->sendClients[prefix].getStatus() == USER)
		return ((this->*(this->replies[ERR_ALREADYREGISTRED]))(message, client));
	if (this->sendClients[prefix].getStatus() != UNKNOWN)
		return ((this->*(this->replies[ERR_PREFIX]))(message, client));
	if (message.getParameters().size() != 4)
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
	this->getChildServer(serverRoll, client->getInfo(SERVERNAME));
	serverRoll.push_back(client->getInfo(SERVERNAME));
	iterator = std::find(serverRoll.begin(), serverRoll.end(), message.getParameter(2));
	if (iterator == serverRoll.end() || this->sendClients[*iterator].getStatus() != SERVER)
		return (CONNECT);
	setUser(message, &this->sendClients[prefix], message.getParameter(1), this->sendClients, message.getParameter(2));
	return (this->*(this->replies[RPL_REGISTERUSER]))(message, &this->sendClients[prefix]);
}

int					Server::userHandler(const Msg &message, Client *client)
{
	client->setCurrentCommand("USER");

	if (client->getStatus() == SERVER)
	{
		this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
		return (this->setRemoteUser(message, client));
	}
	this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
	return (this->setLocalUser(message, client));
}

int					Server::localQuitHandler(const Msg &message, Client *client)
{
	if (client->getStatus() == UNKNOWN)
	{
		if (1 < message.getParameters().size())
			return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
		return ((this->*(this->replies[RPL_QUIT]))(message, client));
	}
	else if (client->getStatus() == USER)
	{
		if (message.getPrefix() != "")
			return ((this->*(replies[ERR_PREFIX]))(message, client));
		if (1 < message.getParameters().size())
			return ((this->*(replies[ERR_NEEDMOREPARAMS]))(message, client));
		(this->*(this->replies[RPL_QUITBROADCAST]))(message, client);
		return ((this->*(this->replies[RPL_QUIT]))(message, client));
	}
	return (CONNECT);
}

int					Server::remoteQuitHandler(const Msg &message, Client *client)
{
	std::string prefix;

	if (message.getPrefix() == "" || 1 < message.getParameters().size())
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
	prefix = message.getPrefix()[0] == ':'
	? message.getPrefix().substr(1, message.getPrefix().length())
	: message.getPrefix();
	if (!this->sendClients.count(prefix)
	|| this->sendClients[prefix].getStatus() != USER
	|| this->getParentServer(prefix) != client->getInfo(SERVERNAME))
		return ((this->*(this->replies[ERR_PREFIX]))(message, client));
	this->sendClients.erase(prefix);
	return ((this->*(this->replies[RPL_QUITBROADCAST]))(message, client));
}

int					Server::quitHandler(const Msg &message, Client *client)
{
	if (client->getStatus() == SERVER) {
		Client *targetUser =  &this->sendClients[message.getPrefix().substr(1)];
		std::vector<std::string> *chRoll = targetUser->getSubscribedChannelRoll();
		if (chRoll != NULL) {
			for (size_t i = 0; i < chRoll->size(); ++i) {
				if (this->localChannelRoll.count((*chRoll)[i])) {
					this->localChannelRoll[(*chRoll)[i]].leaveUser(targetUser);
					if (this->localChannelRoll[(*chRoll)[i]].getdigitsOfUsers() == 0)
						this->localChannelRoll.erase((*chRoll)[i]);
				}
				if (this->remoteChannelRoll.count((*chRoll)[i])) {
					this->remoteChannelRoll[(*chRoll)[i]].leaveUser(targetUser);
					if (this->remoteChannelRoll[(*chRoll)[i]].getdigitsOfUsers() == 0)
						this->remoteChannelRoll.erase((*chRoll)[i]);
				}
			}
		}
		delete chRoll;
	}
	if (client->getStatus() == SERVER)
		return (this->remoteQuitHandler(message, client));
	return (this->localQuitHandler(message, client));
}
