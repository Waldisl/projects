#include "Server.hpp"

int		Server::rRegisterUserHandler(const Msg &message, Client *client) {
	std::map<std::string, Channel>::iterator chanIt;
	Client *targetClient;

	(this->*(this->replies[RPL_NICKBROADCAST]))(message, client);
	(this->*(this->replies[RPL_USERBROADCAST]))(message, client);
	if (client->getInfo(USERMODE) != "")
		(this->*(this->replies[RPL_USERMODEBROADCAST]))(message, client);
	client->setStatus(USER);
	targetClient = &this->sendClients[client->getInfo(NICK)];
	targetClient->setStatus(USER);

	for (chanIt = this->localChannelRoll.begin(); chanIt != this->localChannelRoll.end(); ++chanIt)
	{
		if (chanIt->second.isMatchMask(chanIt->second.getInvitRoll(), getClientPrefix(targetClient)))
			targetClient->setInviteChanRoll(chanIt->first);
	}
	for (chanIt = this->remoteChannelRoll.begin(); chanIt != this->remoteChannelRoll.end(); ++chanIt)
	{
		if (chanIt->second.isMatchMask(chanIt->second.getInvitRoll(), getClientPrefix(targetClient)))
			targetClient->setInviteChanRoll(chanIt->first);
	}
	return (CONNECT);
}

int		Server::rWelcomeMsgHandler(const Msg &message, Client *client)
{
	(this->*(this->replies[RPL_WELCOME]))(message, client);
	(this->*(this->replies[RPL_YOURHOST]))(message, client);
	(this->*(this->replies[RPL_CREATED]))(message, client);
	(this->*(this->replies[RPL_MYINFO]))(message, client);
	(this->*(this->replies[RPL_LUSERCLIENT]))(message, client);
	(this->*(this->replies[RPL_LUSERCHANNELS]))(message, client);
	(this->*(this->replies[RPL_LUSERME]))(message, client);
	(this->*(this->replies[RPL_MOTD]))(message, client);
	sendChannelRolls(client);
	return (CONNECT);
}

static std::string getUserPrefix(Client *client)
{
	std::string returnString;

	returnString += client->getInfo(NICK);
	returnString += std::string("!~");
	returnString += client->getInfo(USERNAME);
	returnString += std::string("@");
	returnString += client->getInfo(HOSTNAME);
	return (returnString);
}

int		Server::rWelcomeHandler(const Msg &message, Client *client)
{
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	parameters = client->getInfo(NICK);
	parameters += std::string(" :Welcome to the Internet Relay Network ");
	parameters += getUserPrefix(client);
	sendMsg = Msg(this->prefix, RPL_WELCOME, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rYourHostHandler(const Msg &message, Client *client)
{
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	parameters = client->getInfo(NICK);
	parameters += std::string(" :Your host is ");
	parameters += this->serverName;
	parameters += std::string(", running version ");
	parameters += this->version;
	sendMsg = Msg(this->prefix, RPL_YOURHOST, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rCreatedHandler(const Msg &message, Client *client)
{
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	parameters = client->getInfo(NICK);
	parameters += std::string(" :This server has been started ");
	parameters += getTimestamp(this->startTime, false);
	sendMsg = Msg(this->prefix, RPL_CREATED, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rMyInfoHandler(const Msg &message, Client *client)
{
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	parameters = client->getInfo(NICK);
	parameters += std::string(" ");
	parameters += this->serverName;
	parameters += std::string(" ");
	parameters += this->version;
	parameters += std::string(" ");
	parameters += this->userMode;
	parameters += std::string(" ");
	parameters += this->chMode;
	sendMsg = Msg(this->prefix, RPL_MYINFO, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

static void		countServerConnections(std::map<std::string, Client> &sendClients,
							int &userCount, int &serviceCount, int &serverCount)
{
	std::map<std::string, Client>::iterator	iterator;

	userCount = 0;
	serviceCount = 0;
	serverCount = 0;
	for(iterator = sendClients.begin(); iterator != sendClients.end(); ++iterator)
	{
		if (iterator->second.getStatus() == SERVER)
			++serverCount;
		else if (iterator->second.getStatus() == USER)
			++userCount;
		else if (iterator->second.getStatus() == SERVICE)
			++serviceCount;
	}
}

int		Server::rLUserClientHandler(const Msg &message, Client *client)
{
	std::stringstream	stream;
	std::string			parameters;
	Msg				sendMsg;
	int					userCount;
	int					serviceCount;
	int					serverCount;

	(void)message;
	countServerConnections(this->sendClients, userCount, serviceCount, serverCount);
	parameters = client->getInfo(NICK);
	parameters += std::string(" :There are ");
	stream << userCount;
	parameters += stream.str();
	stream.str("");
	parameters += std::string(" users and ");
	stream << serviceCount;
	parameters += stream.str();
	stream.str("");
	parameters += std::string(" services on ");
	stream << ++serviceCount;
	parameters += stream.str();
	parameters += std::string(" servers");
	sendMsg = Msg(this->prefix, RPL_LUSERCLIENT, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rLUserChannelHandler(const Msg &message, Client *client)
{
	std::stringstream	stream;
	std::string			parameters;
	Msg				sendMsg;

	(void)message;
	parameters = client->getInfo(NICK);
	parameters += std::string(" ");
	stream << (this->localChannelRoll.size() + this->remoteChannelRoll.size());
	parameters += stream.str();
	parameters += std::string(" :chs formed");
	sendMsg = Msg(this->prefix, RPL_LUSERCHANNELS, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rLUserMeHandler(const Msg &message, Client *client)
{
	std::stringstream	stream;
	std::string			parameters;
	Msg				sendMsg;

	(void)message;
	parameters = client->getInfo(NICK);
	parameters += std::string(" :I have ");
	stream << this->clientRoll.size();
	parameters += stream.str();
	stream.str("");
	parameters += std::string(" users, ");
	stream << this->serviceRoll.size();
	parameters += stream.str();
	stream.str("");
	parameters += std::string(" services and ");
	stream << this->serviceRoll.size();
	parameters += stream.str();
	stream.str("");
	parameters += std::string(" servers");
	sendMsg = Msg(this->prefix, RPL_LUSERME, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rMOTDHandler(const Msg &message, Client *client)
{
	(this->*(this->replies[RPL_MOTDSTART]))(message, client);
	(this->*(this->replies[RPL_MOTDCONTENT]))(message, client);
	(this->*(this->replies[RPL_ENDOFMOTD]))(message, client);
	return (CONNECT);
}

int		Server::rMOTDStartHandler(const Msg &message, Client *client)
{
	std::string	parameters;
	Msg		sendMsg;

	(void)message;
	parameters = client->getInfo(NICK);
	parameters += std::string(" :- ");
	parameters += this->serverName;
	parameters += std::string(" message of the day");
	sendMsg = Msg(this->prefix, RPL_MOTDSTART, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rEndOfMOTDHandler(const Msg &message, Client *client)
{
	std::string	parameters;
	Msg		sendMsg;

	(void)message;
	parameters = client->getInfo(NICK);
	parameters += std::string(" :End of MOTD command");
	sendMsg = Msg(this->prefix, RPL_ENDOFMOTD, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rMOTDContentHandler(const Msg &message, Client *client)
{
	std::ifstream	stream;
	std::string		prefix;
	std::string		readResult;
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	prefix = client->getInfo(NICK);
	prefix += std::string(" :- ");
	stream.open(this->motdDir);
	if (!stream)
	{
		std::cerr << ERROR_FILE_OPEN_FAIL << std::endl;
		parameters = prefix;
		parameters += std::string("42cursus c5 ft_irc made by btwee seunkim dakim");
		sendMsg = Msg(this->prefix, RPL_MOTDCONTENT, parameters);
		this->sendMsg(sendMsg, client);
		return (CONNECT);
	}
	while (stream)
	{
		getline(stream, readResult);
		if (readResult != "")
		{
			parameters = prefix;
			parameters += readResult.substr(0, 79);
			sendMsg = Msg(this->prefix, RPL_MOTDCONTENT, parameters);
			this->sendMsg(sendMsg, client);
		}
	}
	stream.close();
	return (CONNECT);
}


int		Server::rNickHandler(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	prefix = std::string(":");
	prefix += client->getInfo(NICK);
	prefix += std::string("!~");
	prefix += client->getInfo(USERNAME);
	prefix += std::string("@");
	prefix += client->getInfo(HOSTNAME);
	parameters = std::string(":");
	parameters += message.getParameter(0);
	sendMsg = Msg(prefix, RPL_NICK, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rNickBroadcastHandler(const Msg &message, Client *client)
{
	std::string			prefix;
	std::string			parameters;
	Msg				sendMsg;

	if (client->getStatus() == UNKNOWN)
	{
		prefix = std::string("");
		parameters = client->getInfo(NICK);
		parameters += std::string(" :1");
	}
	else
	{
		prefix = std::string(":");
		prefix += client->getInfo(NICK);
		parameters = std::string(":");
		parameters += message.getParameter(0);
	}
	sendMsg = Msg(prefix, RPL_NICK, parameters);
	this->broadcastMsg(sendMsg, (!this->clientRoll.count(client->getInfo(NICK))
	? &this->acceptClients[client->getFd()] : client));
	return (CONNECT);
}

int				Server::rSquitBroadcastHandler(const Msg &message, Client *client)
{
	std::string				prefix;
	std::string				parameters;
	Msg					sendMsg;

	parameters = client->getInfo(SERVERNAME);
	if (message.getCommand() == TIMEOUT)
	{
	    prefix = ':' + message.getParameter(0);
        parameters += " :ERROR :Ping timeout";
    }
    else if (!message.getParameters().empty())
	{
		prefix = message.getPrefix();
		parameters += std::string(" :ID \"");
		parameters += message.getParameter(0);
		parameters += std::string("\" already registered");
	}
	else
	{
		prefix = std::string(":");
		prefix += client->getInfo(SERVERNAME);
		parameters += std::string(" :");
		if (this->serverRoll.count(client->getInfo(SERVERNAME)))
			parameters += std::string("Client closed cnt");
		else
		{
			parameters += this->serverName;
			parameters += std::string(" ");
			parameters += client->getInfo(UPLINKSERVER);
		}
	}
	sendMsg = Msg(prefix, RPL_SQUIT, parameters);
	this->broadcastMsg(sendMsg, client);
	return (CONNECT);
}

int				Server::rQuitBroadcastHandler(const Msg &message, Client *client)
{
	std::string			prefix;
	std::string			parameters;
	Msg				sendMsg;

	prefix = std::string(":");
	parameters = std::string(":");
	if (message.getCommand() == TIMEOUT)
	{
	    prefix = message.getPrefix();
        parameters += "ERROR :Ping Timeout";
    }
    else if (message.getCommand() == RPL_NICK)
	{
		prefix += message.getParameter(0);
		parameters += std::string("Nick collision");
	}
	else
	{
		prefix += client->getStatus() == USER
		? client->getInfo(NICK)
		: (message.getPrefix()[0] == ':' ? message.getPrefix().substr(1, message.getPrefix().length()) : message.getPrefix());
		parameters += !message.getParameters().empty()
		? (message.getParameter(0)[0] == ':' ? message.getParameter(0).substr(1, message.getParameter(0).length()) : message.getParameter(0))
		: std::string("Client closed cnt");
	}
	sendMsg = Msg(prefix, RPL_QUIT, parameters);
	this->broadcastMsg(sendMsg, client);
	return (CONNECT);
}

int				Server::rQuitHandler(const Msg &message, Client *client)
{
	std::string			parameters;
	Msg				sendMsg;

	parameters = std::string(":");
	if (message.getParameters().empty())
		parameters += std::string("Closing cnt");
	else
	{
		parameters += std::string("\"");
		parameters += message.getParameter(0)[0] == ':'
		? message.getParameter(0).substr(1, message.getParameter(0).length())
		: message.getParameter(0);
		parameters += std::string("\"");
	}
	sendMsg = Msg(std::string(""), ERROR_STR, parameters);
	this->sendMsg(sendMsg, client);
	return (DISCONNECT);
}

int				Server::rUserBroadcastHandler(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	prefix = std::string(":");
	prefix += client->getInfo(NICK);
	parameters = std::string("~");
	parameters += client->getInfo(USERNAME);
	parameters += std::string(" ");
	parameters += client->getInfo(ADDRESS);
	parameters += std::string(" ");
	parameters += (!this->clientRoll.count(client->getInfo(NICK))
	? this->acceptClients[client->getFd()].getInfo(SERVERNAME) : client->getInfo(UPLINKSERVER));
	parameters += std::string(" :");
	parameters += client->getInfo(REALNAME);
	sendMsg = Msg(prefix, RPL_USER, parameters);
	this->broadcastMsg(sendMsg, (!this->clientRoll.count(client->getInfo(NICK))
	? &this->acceptClients[client->getFd()] : client));
	return (CONNECT);
}

int				Server::rUserModeBroadcastHandler(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	prefix = std::string(":");
	prefix += client->getInfo(NICK);
	parameters = client->getInfo(NICK);
	parameters += std::string(" +");
	parameters += client->getInfo(USERMODE);
	sendMsg = Msg(prefix, RPL_MODE, parameters);
	this->broadcastMsg(sendMsg, (!this->clientRoll.count(client->getInfo(NICK))
	? &this->acceptClients[client->getFd()] : client));
	return (CONNECT);
}

int		Server::rPassHandler(const Msg &message, Client *client)
{
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	client->setCurrentCommand("PASS");
	parameters = this->pass;
	sendMsg = Msg("", RPL_PASS, parameters + " " + this->version + " ada|sdasdasd");
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rHostHandler(const Msg &message, Client *client)
{
	std::string		parameters;
	Msg			sendMsg;

	(void)message;
	client->setCurrentCommand("SERVER");
	parameters += this->serverName;
	parameters += std::string(" ");
	parameters += client->getInfo(HOPCOUNT);
	if (message.getParameters().size() == 4)
		parameters += std::string(" 0 ");
	else
		parameters += std::string(" ");
	parameters += this->info;
	sendMsg = Msg(this->prefix, RPL_SERVER, parameters);
	this->sendMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rOtherServerHandler(const Msg &message, Client *client)
{
	std::map<std::string, Client>::iterator	it;
	std::string								prefix;
	std::string								parameters;
	Msg									sendMsg;

	(void)message;
	for(it = this->sendClients.begin(); it != this->sendClients.end(); ++it)
	{
		if (it->second.getInfo(SERVERNAME) != client->getInfo(SERVERNAME))
		{
			if (it->second.getStatus() == SERVER)
			{
				prefix = std::string(":");
				prefix += it->second.getInfo(UPLINKSERVER);
				parameters = it->second.getInfo(SERVERNAME);
				parameters += std::string(" ");
				parameters += std::to_string(ft_atoi(it->second.getInfo(HOPCOUNT).c_str()) + 1);
				parameters += std::string(" 0 ");
				parameters += it->second.getInfo(SERVERINFO);
				client->setCurrentCommand("SERVER");
				sendMsg = Msg(prefix, RPL_SERVER, parameters);
				this->sendMsg(sendMsg, client);
			}
			else
			{
				prefix = "";
				parameters = it->second.getInfo(NICK);
				parameters += std::string(" :1");
				client->setCurrentCommand("NICK");
				sendMsg = Msg(prefix, RPL_NICK, parameters);
				this->sendMsg(sendMsg, client);
				parameters.clear();
				prefix = std::string(":");
				prefix += it->second.getInfo(NICK);
				parameters = std::string("~");
				parameters += it->second.getInfo(USERNAME);
				parameters += " ";
				parameters += it->second.getInfo(ADDRESS);
				parameters += " ";
				parameters += it->second.getInfo(HOSTNAME);
				parameters += " :";
				parameters += it->second.getInfo(REALNAME);
				client->setCurrentCommand("USER");
				sendMsg = Msg(prefix, RPL_USER, parameters);
				this->sendMsg(sendMsg, client);
			}
		}
	}
	sendChannelRolls(client);
	return (CONNECT);
}

int		Server::rServerBroadcastHandler(const Msg &message, Client *client)
{
	std::string								prefix;
	std::string								parameters;
	Msg									sendMsg;

	(void)message;
	if (message.getPrefix() == "")
		prefix = this->prefix;
	else
		prefix += message.getPrefix();
	parameters = message.getParameter(0);
	parameters += std::string(" ");
	parameters += std::to_string(ft_atoi(message.getParameter(1).c_str()) + 1);
	parameters += std::string(" 0 ");
	parameters += client->getInfo(SERVERINFO);
	sendMsg = Msg(prefix, RPL_SERVER, parameters);
	this->broadcastMsg(sendMsg, client);
	return (CONNECT);
}

int		Server::rServerHandler(const Msg &message, Client *client)
{
	if (message.getPrefix() == "")
	{
		(this->*(this->replies[RPL_PASS]))(message, client);
		(this->*(this->replies[RPL_HOST]))(message, client);
		(this->*(this->replies[RPL_OTHERSERVER]))(message, client);
	}
	(this->*(this->replies[RPL_SERVERBROADCAST]))(message, client);
	return (CONNECT);
}

int				Server::rKillHandler(const Msg &message, Client *client)
{
	std::string		prefix;
	std::string		parameters;
	Msg			sendMsg;

	prefix = this->prefix;
	parameters = message.getParameter(0);
	parameters += std::string(" :Nick collision");
	sendMsg = Msg(prefix, RPL_KILL, parameters);
	this->sendMsg(sendMsg, client);
	this->broadcastMsg(sendMsg, client);
	return (CONNECT);
}

int				Server::rReplyHandler(const Msg &message, Client *client)
{
    (void)client;
    if (this->sendClients.count(message.getParameter(0)))
        sendMsg(message, &this->sendClients[message.getParameter(0)]);
	return (CONNECT);
}

int				Server::rStatsM(const Msg &message, Client *client)
{
	std::string parameter;

	if (message.getPrefix().empty())
		parameter = client->getInfo(NICK);
	else
		parameter = message.getPrefix().substr(1, message.getPrefix().length());
	for (std::map<std::string, Info>::iterator it = this->infosPerCommand.begin(); it != this->infosPerCommand.end(); ++it)
	{
		if (std::isalpha(it->first[0]) && (it->second.getLocalCount() != "0" || it->second.getRemoteCount() != "0"))
		{
			sendMsg(Msg(this->prefix
								, RPL_STATSCOMMANDS
								, parameter + " " + it->first
								+ " " + it->second.getLocalCount()
								+ " " + it->second.getBytes()
								+ " " + it->second.getRemoteCount())
								, client);
		}
	}
	return (CONNECT);
}

int				Server::rStatsL(const Msg &message, Client *client)
{
	std::string parameter;
	std::time_t	current;

	current = std::time(NULL);
	for (strClientPtrIter it = this->clientRoll.begin(); it != this->clientRoll.end(); ++it)
	{
		if (message.getPrefix().empty())
			parameter = client->getInfo(NICK);
		else
			parameter = message.getPrefix().substr(1, message.getPrefix().length());
		parameter += " ";
		parameter += it->second->getInfo(NICK);
		parameter += "!~";
		parameter += it->second->getInfo(USERNAME);
		parameter += "@";
		parameter += it->second->getInfo(HOSTNAME);
		sendMsg(Msg(this->prefix
							, RPL_STATSLINKINFO
							, parameter
							+ " " + it->second->getQueryData(SENDQUEUE)
							+ " " + it->second->getQueryData(SENDMSG)
							+ " " + it->second->getQueryData(SENDBYTES)
							+ " " + it->second->getQueryData(RECVMSG)
							+ " " + it->second->getQueryData(RECVBYTES)
							+ " :" + std::to_string(current - it->second->getStartTime()))
							, client);
	}

	for (strClientPtrIter it = this->serverRoll.begin(); it != this->serverRoll.end(); ++it)
	{
		if (message.getPrefix().empty())
			parameter = client->getInfo(NICK);
		else
			parameter = message.getPrefix().substr(1, message.getPrefix().length());
		parameter += " ";
		parameter += it->second->getInfo(SERVERNAME);
		sendMsg(Msg(this->prefix
							, RPL_STATSLINKINFO
							, parameter
							+ " " + it->second->getQueryData(SENDQUEUE)
							+ " " + it->second->getQueryData(SENDMSG)
							+ " " + it->second->getQueryData(SENDBYTES)
							+ " " + it->second->getQueryData(RECVMSG)
							+ " " + it->second->getQueryData(RECVBYTES)
							+ " :" + std::to_string(current - it->second->getStartTime()))
							, client);
	}
	return (CONNECT);
}


int				Server::rStatsU(const Msg &message, Client *client)
{
	std::string parameter;
	time_t		timeDiff;

	timeDiff = std::time(NULL) - this->startTime;
	if (message.getPrefix().empty())
		parameter = client->getInfo(NICK);
	else
		parameter = message.getPrefix().substr(1, message.getPrefix().length());
	parameter += " :Server Up ";
	parameter += getTimestamp(timeDiff, true);
	sendMsg(Msg(this->prefix
						, RPL_STATSUPTIME
						, parameter), client);
	return (CONNECT);
}

int				Server::rEndOfStats(const Msg &message, Client *client)
{
	std::string option;
	std::string parameter;

	if (message.getParameters().empty())
		option = "*";
	else
		option = message.getParameter(0)[0];
	if (message.getPrefix().empty())
		parameter = client->getInfo(NICK);
	else
		parameter = message.getPrefix().substr(1, message.getPrefix().length());
	sendMsg(Msg(this->prefix
						, RPL_ENDOFSTATS
						, parameter	+ " " + option
						+ " :End of STATS report"
						)
						, client);
	return (CONNECT);
}

int				Server::rEndOfLinks(const Msg &message, Client *client)
{
	std::string option;
	std::string parameter;

	if (message.getParameters().empty())
		option = "*";
	else
		option = message.getParameter(0);
	if (message.getPrefix().empty())
		parameter = client->getInfo(NICK);
	else
		parameter = message.getPrefix().substr(1, message.getPrefix().length());
	sendMsg(Msg(this->prefix
						, RPL_ENDOFLINKS
						, parameter + " " + option
						+ " :End of LINKS list")
						, client);
	return (CONNECT);
}

int				Server::rInviting(const Msg &message, Client *client)
{	
	Client	*targetUser;

	(void) client;
	if (this->clientRoll.find(message.getParameter(0)) != this->clientRoll.end())
	{
		targetUser = this->clientRoll[message.getParameter(0)];
		this->sendMsg(message, targetUser);
	}
	else
		this->sendMsg(message, &this->sendClients[message.getParameter(0)]);
	return (CONNECT);
}