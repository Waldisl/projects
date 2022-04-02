#include "Server.hpp"

int		Server::eNoNickNameGivenHandler(const Msg &message, Client *client)
{
	std::string	parameters;

	(void)message;
	parameters = std::string(":No nickname given");
	Msg sendMsg(this->prefix, ERR_NONICKNAMEGIVEN, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eNeedMoreParamsHandler(const Msg &message, Client *client)
{
	std::string parameters;
	Msg		sendMsg;

	parameters = client->getInfo(NICK) == "" ? "*" : client->getInfo(NICK);
	parameters += std::string(" ");
	parameters += message.getCommand();
	parameters += std::string(" :Syntax error");
	sendMsg = Msg(this->prefix, ERR_NEEDMOREPARAMS, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eErroneusNickNameHandler(const Msg &message, Client *client)
{
	std::string	parameters;
	Msg		sendMsg;

	parameters = message.getParameter(0);
	if (client->getStatus() == SERVER)
	{
		parameters += std::string(" ");
		parameters += client->getInfo(SERVERNAME);
	}
	parameters += std::string(" :Erroneous nickname");
	sendMsg = Msg(this->prefix, ERR_ERRONEUSNICKNAME, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eNickNameInUseHandler(const Msg &message, Client *client)
{
	std::string	parameters;
	Msg		sendMsg;

	parameters = client->getInfo(NICK) == "" ? "*" : client->getInfo(NICK);
	parameters += std::string(" ");
	parameters += message.getParameter(0);
	parameters += std::string(" :Nickname already in use");
	sendMsg = Msg(this->prefix, ERR_NICKNAMEINUSE, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eAlreadyRegisteredHandler(const Msg &message, Client *client)
{
	std::string	parameters;
	Msg		sendMsg;
	int			cntStatus;

	cntStatus = CONNECT;
	if (message.getCommand() != "USER")
	{
		parameters = std::string(":ID ");
		parameters += message.getParameter(0);
		parameters += std::string(" already registered");
		cntStatus = DISCONNECT;
	}
	else if (client->getStatus() == USER)
	{
		parameters = client->getInfo(NICK);
		parameters += std::string(" :Connection already registered");
	}
	else
		parameters = std::string(":Unauthorized command (already registered)");
	sendMsg = Msg(this->prefix, ERR_ALREADYREGISTRED, parameters);
	this->sendMsg(sendMsg, client);
	return (cntStatus);
}

int		Server::ePassUnauthorizedHandler(const Msg &message, Client *client)
{
	std::string	parameters;
	Msg		sendMsg;

	(void)message;
	parameters += std::string(":Access denied: Bad password");
	sendMsg = Msg("", ERROR_STR, parameters);
	this->sendMsg(sendMsg, client);
	return (DISCONNECT);
}

int		Server::eErroneusUserNameHandler(const Msg &message, Client *client)
{
	std::string	parameters;
	Msg		sendMsg;

	parameters = message.getCommand();
	parameters += std::string(" :Erroneous username");
	sendMsg = Msg("", ERROR_STR, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::ePrefixHandler(const Msg &message, Client *client)
{
	std::string	parameters;
	Msg		sendMsg;

	parameters = std::string(":Invalid prefix \"");
	if (!message.getPrefix().empty())
		parameters += message.getPrefix()[0] == ':'
		? message.getPrefix().substr(1, message.getPrefix().length())
		: message.getPrefix();
	parameters += std::string("\"");
	sendMsg = Msg(std::string(""), ERROR_STR, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eNickCollisionHandler(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	prefix = this->prefix;
	parameters = message.getParameter(0);
	parameters += std::string(" :Nick collision");
	sendMsg = Msg(prefix, ERR_NICKCOLLISION, parameters);
	this->sendMsg(sendMsg, client);
	this->discntClient(message, client);
	return (CONNECT);
}

int		Server::eCantKillServerHandler(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	prefix = this->prefix;
	parameters = message.getParameter(0);
	parameters += std::string(" :You can't kill a server!");
	sendMsg = Msg(prefix, ERR_CANTKILLSERVER, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eNoSuchServer(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	prefix = this->prefix;
	if (message.getPrefix().empty())
		parameters = client->getInfo(NICK);
	else
		parameters = message.getPrefix().substr(1, message.getPrefix().length());
	parameters += " ";
	parameters += message.getParameter(0);
	parameters += " :No such server";
	sendMsg = Msg(prefix, ERR_NOSUCHSERVER, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eUnknownCommand(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	prefix = this->prefix;
	if (message.getPrefix().empty())
		parameters = client->getInfo(NICK);
	else
		parameters = message.getPrefix().substr(1, message.getPrefix().length());
	parameters += " ";
	if (!message.getParameters().empty())
		parameters += message.getParameter(0);
	parameters += " :Unknown command";
	sendMsg = Msg(prefix, ERR_UNKNOWNCOMMAND, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}


int		Server::eNotRegistered(const Msg &message, Client *client)
{
	(void)message;
	sendMsg(Msg(this->prefix
						, ERR_NOTREGISTERED
						, "* :Connection not registered")
						, client);
	return (CONNECT);
}

int		Server::eNoRecipients(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	prefix = this->prefix;
	parameters += client->getInfo(NICK);
	parameters += std::string(" :No recipient given (privmsg)");
	sendMsg = Msg(prefix, ERR_NORECIPIENT, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eNoTextToSend(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	prefix = this->prefix;
	parameters += client->getInfo(NICK);
	parameters += std::string(" :No text to send");
	sendMsg = Msg(prefix, ERR_NOTEXTTOSEND, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::eNoSuchNick(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	prefix = this->prefix;
	parameters += client->getInfo(NICK);
	parameters += std::string(" ");
	parameters += message.getParameter(0);
	parameters += std::string(" :No such nick or ch name");
	sendMsg = Msg(prefix, ERR_NOSUCHNICK, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int     Server::eNoOrigin(const Msg &message, Client *client)
{
    (void)message;
    sendMsg(Msg(this->prefix
                        , ERR_NOORIGIN
                        , client->getInfo(NICK)
                        + " :No Origin Specified")
                        , client);
    return (CONNECT);
}

int		Server::eUnknownMode(const Msg &message, Client *client)
{
	sendMsg(Msg(this->prefix
						, ERR_UNKNOWNMODE
						, client->getInfo(NICK)
						+ " " + message.getParameter(1)[0]
						+ " :is unknown mode char"), client);
	return (CONNECT);
}

int		Server::eUserNotInChannel(const Msg &message, Client *client)
{
	sendMsg(Msg(this->prefix
				, ERR_USERNOTINCHANNEL
				, client->getInfo(NICK)
				+ " " + message.getParameter(1)
				+ " " + message.getParameter(0)
				+ " :They aren't on that channnel")
				, client);
	return (CONNECT);
}
int 	Server::eBadChannelKey(const Msg &message, Client *client)
{
	sendMsg(Msg(this->prefix
					 ,ERR_BADCHANNELKEY
					 , client->getInfo(NICK)
					 + " " + message.getParameter(0)
					 + " :Cannot join Channel (+k) -- Wrong Channel Key")
			 		 , client);
	return (CONNECT);
}
int		Server::eInviteOnlyChan(const Msg &message, Client *client)
{
	sendMsg(Msg(this->prefix
				, ERR_INVITEONLYCAHN
				, client->getInfo(NICK)
				+ " " + message.getParameter(0)
				+ " :Cannot join Channel (+i) -- Invited Users Only")
			 	, client);
	return (CONNECT);
}

int 	Server::eBannedFromChan(const Msg &message, Client *client)
{
	sendMsg(Msg(this->prefix
				, ERR_BANNEDFROMCHAN
			 	, client->getInfo(NICK)
			 	+ " " + message.getParameter(0)
			 	+ " :Cannot join Channel (+b) -- You are banned")
				, client);
	return (CONNECT);
}