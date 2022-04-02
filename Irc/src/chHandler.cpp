#include "Server.hpp"

std::vector<std::string>    getChannelNames(const std::string &name)
{
	std::vector<std::string>    names;
	std::stringstream           ss(name);
	std::string                 buffer;

	while (std::getline(ss, buffer, ','))
		names.push_back(buffer);
	return (names);
}

int     Server::joinHandler(const Msg &message, Client *client)
{
	std::string                 check;
	std::string                 chName;
	std::string                 fullChannelName;
	std::string 				modeParam;
	size_t 						modeParamIndex;
	std::vector<std::string>    chNames;
	std::vector<Client *>       joinedUsers;
	Channel                     *targetChannel;
	Client						*targetUser;
	std::map<std::string, Channel>::iterator it;


	client->setCurrentCommand("JOIN");
	if (client->getStatus() == UNKNOWN)
		return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
	else if (client->getStatus() == USER)
		this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
	else
		this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
	if ((check = client->prefixCheck(message)) != "ok")
		return (this->*(this->replies[check]))(message, client);

	if (client->getStatus() == USER)
	{
		chNames = getChannelNames(message.getParameter(0));
		for (int i = 0; i < (int)chNames.size(); i++)
		{
			fullChannelName = chNames[i];

			if(client->findChannel(fullChannelName))
				continue;
			if(fullChannelName.at(0) == '#' || fullChannelName.at(0) == '&')
			{
				chName = fullChannelName.substr(1);

				if ((it = this->localChannelRoll.find(fullChannelName)) != this->localChannelRoll.end())
					targetChannel = &it->second;
				else if((it = this->remoteChannelRoll.find(fullChannelName)) != this->remoteChannelRoll.end())
					targetChannel = &it->second;
				else
				{
					this->localChannelRoll[fullChannelName] = Channel(fullChannelName);
					targetChannel = &this->localChannelRoll[fullChannelName];
				}

				modeParamIndex = 1;
				targetUser = &this->sendClients[client->getInfo(NICK)];
				if (targetChannel->getMode() & MODE_K && !targetChannel->checkKey(message.getParameter(modeParamIndex)))
					return (this->*(this->replies[ERR_BADCHANNELKEY]))(message, targetUser);
				if (targetChannel->getMode() & MODE_LI && !targetUser->isInvited(fullChannelName))
					return (this->*(this->replies[ERR_INVITEONLYCAHN]))(message, targetUser);
				if (targetChannel->getMode() & MODE_B && targetChannel->isBanned(getClientPrefix(targetUser)))
				{
					if (!(targetChannel->getMode() & MODE_E) || !(targetChannel->isExcept(getClientPrefix(targetUser))))
						return (this->*(this->replies[ERR_BANNEDFROMCHAN]))(message, targetUser);
				}


				client->joinChannel(targetChannel, fullChannelName);
				targetUser->delInviteChanRoll(fullChannelName);
				targetUser->joinChannel(targetChannel, fullChannelName);

				targetChannel->enterUser(client);


				joinedUsers = targetChannel->getUsersRoll(this->serverName);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
				{
					if (joinedUsers[i]->getInfo(HOSTNAME) == this->serverName)
						this->sendMsg(Msg(":" + getClientPrefix(client), "JOIN", ":" + fullChannelName), joinedUsers[i]);
				}

				this->sendMsg(Msg(this->prefix, RPL_NAMREPLY, client->getInfo(NICK)
																	  + " = "
																	  + fullChannelName
																	  + " :"
																	  + targetChannel->getUserNameRoll()), client);

				this->sendMsg(Msg(this->prefix, RPL_ENDOFNAMES, client->getInfo(NICK)
																		+ " "
																		+ fullChannelName
																		+ " :End of NAMES list"), client);

				if (fullChannelName.at(0) == '#')
					this->broadcastMsg(Msg(":" + client->getInfo(NICK), "JOIN", fullChannelName), client);
			}

			else
				this->sendMsg(Msg(this->prefix, ERR_NOSUCHCHANNEL, client->getInfo(NICK) + " " + fullChannelName + " No such ch"), client);
			++modeParamIndex;
		}

	}
	else if (client->getStatus() == SERVER)
	{
		std::string     clientName;
		Client          *targetClient;

		clientName = message.getPrefix().substr(1);
		targetClient = &this->sendClients[clientName];

		fullChannelName = message.getParameter(0);
		chName = message.getParameter(0).substr(1);

		if ((it = this->localChannelRoll.find(fullChannelName)) != this->localChannelRoll.end())
			targetChannel = &it->second;
		else if((it = this->remoteChannelRoll.find(fullChannelName)) != this->remoteChannelRoll.end())
			targetChannel = &it->second;
		else
		{
			this->remoteChannelRoll[fullChannelName] = Channel(fullChannelName);
			targetChannel = &this->remoteChannelRoll[fullChannelName];
		}
		targetClient->joinChannel(targetChannel, message.getParameter(0));
		joinedUsers = targetChannel->getUsersRoll(this->serverName);
		for (int i = 0; i < (int)joinedUsers.size(); i++)
			this->sendMsg(Msg(getClientPrefix(joinedUsers[i])
				, "JOIN"
				, ":" + message.getParameter(0))
				, joinedUsers[i]);
		targetChannel->enterUser(targetClient);
		this->broadcastMsg(message, client);
	}
	return (CONNECT);
}

std::string getPartMsg(const Msg& message)
{
	std::string returnMsg;

	if (message.getParameters().size() == 1)
		returnMsg = "";
	else if (message.getParameters().size() == 2)
	{
		if (message.getParameter(1).at(0) == ':')
			returnMsg = message.getParameter(1).substr(1);
		else
			returnMsg = message.getParameter(1);
	}
	else
	{
		returnMsg = message.getParameter(1).substr(1);
		for (int i = 2; i < (int)message.getParameters().size(); i++)
			returnMsg += message.getParameter(i);
	}
	return (returnMsg);
}

int     Server::partHandler(const Msg &message, Client *client)
{
	std::string                 chName;
	std::vector<std::string>    chNames;
	std::vector<Client *>       joinedUsers;
	Channel                     *targetChannel = NULL;
	std::map<std::string, Channel>::iterator it;

	client->setCurrentCommand("PART");

	if (!(message.getParameters().size() == 1 ||
		  (message.getParameters().size() == 2) ||
		  (message.getParameters().size() > 2 && message.getParameter(1).at(0) == ':')))
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));

	if (client->getStatus() == USER)
	{
		chNames = getChannelNames(message.getParameter(0));
		for (int i = 0; i < (int)chNames.size(); i++)
		{
			chName = chNames[i];

			if (client->findChannel(chName))
			{
				if ((it = this->localChannelRoll.find(chName)) != this->localChannelRoll.end())
					targetChannel = &it->second;
				else if ((it = this->remoteChannelRoll.find(chName)) != this->remoteChannelRoll.end())
					targetChannel = &it->second;

				client->leaveChannel(chName);
				this->sendClients[client->getInfo(NICK)].leaveChannel(chName);

				targetChannel->leaveUser(client);

				if (targetChannel->getdigitsOfUsers() == 0)
				{
					if (this->localChannelRoll.find(chName) != this->localChannelRoll.end())
						this->localChannelRoll.erase(chName);
					else if (this->remoteChannelRoll.find(chName) != this->remoteChannelRoll.end())
						this->remoteChannelRoll.erase(chName);
					this->sendMsg(Msg(":" + getClientPrefix(client), "PART", chName + " :" + getPartMsg(message)), client);

					if (chName.at(0) == '#')
						this->broadcastMsg(Msg(":" + client->getInfo(NICK), "PART", chName + " :" + getPartMsg(message)), client);

					continue;
				}

				this->sendMsg(Msg(":" + getClientPrefix(client), "PART", chName + " :" + getPartMsg(message)), client);

				joinedUsers = targetChannel->getUsersRoll(this->serverName);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
					this->sendMsg(Msg(":" + getClientPrefix(client), "PART", chName + " :" + getPartMsg(message)), joinedUsers[i]);


				if (chName.at(0) == '#')
					this->broadcastMsg(Msg(":" + client->getInfo(NICK), "PART", chName + " :" + getPartMsg(message)), client);
			}

			else if (this->localChannelRoll.find(chName) != this->localChannelRoll.end())
				this->sendMsg(Msg(this->prefix, ERR_NOTONCHANNEL, client->getInfo(NICK) + " " + chName + " :You are not on that ch"), client);

			else
				this->sendMsg(Msg(this->prefix, ERR_NOSUCHCHANNEL, client->getInfo(NICK) + " " + chName + " :No such ch"), client);
		}
	}

	else if (client->getStatus() == SERVER)
	{
		std::string clientName;
		Client      *targetClient;

		clientName = message.getPrefix().substr(1);
		targetClient = &this->sendClients[clientName];

		chName = message.getParameter(0);

		if ((it = this->localChannelRoll.find(chName)) != this->localChannelRoll.end())
			targetChannel = &it->second;
		else if ((it = this->remoteChannelRoll.find(chName)) != this->remoteChannelRoll.end())
			targetChannel = &it->second;

		targetClient->leaveChannel(chName);
		targetChannel->leaveUser(targetClient);

		joinedUsers = targetChannel->getUsersRoll(this->serverName);
		for (int i = 0; i < (int)joinedUsers.size(); i++)
			this->sendMsg(Msg(":" + getClientPrefix(targetClient), "PART", chName + " :" + getPartMsg(message)), joinedUsers[i]);

		if (targetChannel->getdigitsOfUsers() == 0)
		{
			if (this->localChannelRoll.find(chName) != this->localChannelRoll.end())
				this->localChannelRoll.erase(chName);
			else if (this->remoteChannelRoll.find(chName) != this->remoteChannelRoll.end())
				this->remoteChannelRoll.erase(chName);
		}

		this->broadcastMsg(message, client);
	}

	return (CONNECT);
}

std::string     getSec(const Msg &message)
{
	std::string returnSec;


	if (message.getParameter(1) == ":" && message.getParameters().size() == 2)
	{
		returnSec = "";
		return (returnSec);
	}
	if (message.getParameter(1).at(0) == ':')
	{
		returnSec = message.getParameter(1).substr(1);
		for (int i = 2; i < (int)message.getParameters().size(); i++)
			returnSec += (" " + message.getParameter(i));
	}
	else
		returnSec = message.getParameter(1);
	return (returnSec);
}

int     Server::topicHandler(const Msg &message, Client *client)
{
	std::string             topic;
	std::string             chName;
	Channel                 *targetChannel = NULL;
	std::map<std::string, Channel>::iterator it;
	std::vector<Client *>   joinedUsers;
	std::time_t             time;

	client->setCurrentCommand("TOPIC");

	if (!((message.getParameters().size() >= 1 && message.getParameters().size() <= 2)
		  || (message.getParameters().size() > 2 && message.getParameter(0).at(0) == ':')))
		return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));

	if (client->getStatus() == USER)
	{
		chName = message.getParameter(0);

		if (this->localChannelRoll.find(chName) == this->localChannelRoll.end()
			&& this->remoteChannelRoll.find(chName) == this->remoteChannelRoll.end())
		{
			this->sendMsg(Msg(this->prefix, ERR_NOSUCHCHANNEL, client->getInfo(NICK) + " " + chName + " :No such ch"), client);
			return (CONNECT);
		}

		targetChannel = client->findChannel(chName);

		if (targetChannel == nullptr)
		{
			this->sendMsg(Msg(this->prefix, ERR_NOTONCHANNEL, client->getInfo(NICK) + " " + chName + " :You are not on that ch"), client);
			return(CONNECT);
		}

		if (message.getParameters().size() == 1)
		{
			if (targetChannel)
			{

				if (targetChannel->getSec() == "")    // 331
					this->sendMsg(Msg(this->prefix, RPL_NOTOPIC, client->getInfo(NICK) + " " + chName + " :No topic is set"), client);

				else
				{

					this->sendMsg(Msg(this->prefix, RPL_TOPIC, client->getInfo(NICK) + " " + chName + " :" + targetChannel->getSec()), client);

					time = std::time(0);

					this->sendMsg(Msg(this->prefix, RPL_TOPICWHOTIME, client->getInfo(NICK) + " " + chName + " " + client->getInfo(NICK) + " " + std::to_string(time)), client);
				}
			}
		}
		else if (message.getParameters().size() >= 2)
		{
			topic = getSec(message);
			targetChannel->setSec(topic);

			joinedUsers = targetChannel->getUsersRoll(this->serverName);
			for (int i = 0; i < (int)joinedUsers.size(); i++)
				this->sendMsg(Msg(getClientPrefix(client), "TOPIC", chName + " :" + topic), joinedUsers[i]);

			if (message.getParameter(0).at(0) == '#')
				this->broadcastMsg(Msg(":" + client->getInfo(NICK), "TOPIC", chName + " :" + topic), client);
		}
	}
	else if (client->getStatus() == SERVER)
	{
		std::string    clientName;
		Client         *targetClient;


		clientName = message.getPrefix().substr(1);
		std::cout << "clientName: " << clientName << std::endl;
		targetClient = &this->sendClients[clientName];
		std::cout << "targetClient: " << targetClient->getInfo(NICK) << std::endl;

		chName = message.getParameter(0);
		std::cout << "chName = " << chName << std::endl;

		if ((it = this->localChannelRoll.find(chName)) != this->localChannelRoll.end())
			targetChannel = &it->second;
		else if((it = this->remoteChannelRoll.find(chName)) != this->remoteChannelRoll.end())
			targetChannel = &it->second;
		// else
		// {
		//     this->remoteChannelRoll[chName] = Channel(chName);
		//     targetChannel = &this->remoteChannelRoll[chName];
		// }
		topic = getSec(message);
		targetChannel->setSec(topic);
		std::cout << "targetChannel = " << targetChannel->getName() << std::endl;
		std::cout << "this->serverName = " << this->serverName << std::endl;
		joinedUsers = targetChannel->getUsersRoll(this->serverName);
		for (int i = 0; i < (int)joinedUsers.size(); i++)
			this->sendMsg(Msg(getClientPrefix(joinedUsers[i]), "TOPIC", message.getParameter(0) + " :" + topic), joinedUsers[i]);
		this->broadcastMsg(message, client);
	}
	return (CONNECT);
}

void 		Server::outExceptionRoll(Channel &ch, Client *client)
{
	std::set<std::string>::iterator it;
	std::set<std::string> 	&exceptRoll = ch.getExceptionRoll();

	it = exceptRoll.begin();
	for (; it != exceptRoll.end(); ++it)
	{
		this->sendMsg(Msg(this->prefix
			, RPL_EXCEPTLIST
			, client->getInfo(NICK)
			  + " " + ch.getName()
			  + " " + *it
			  + " " + client->getInfo(NICK)
			  + std::to_string(std::time(NULL)))
			, client);
	}
	this->sendMsg(Msg(this->prefix
		, RPL_ENDOFEXCEPTLIST
		, client->getInfo(NICK)
		  + " " + ch.getName()
		  + " :End of ch exception list")
		, client);
}
void 		Server::outInvitRoll(Channel &ch, Client *client)
{
	std::set<std::string>::iterator it;
	std::set<std::string> &invitationRoll = ch.getInvitRoll();

	it = invitationRoll.begin();
	for (; it != invitationRoll.end(); ++it)
	{
		this->sendMsg(Msg(this->prefix
			, RPL_INVITELIST
			, client->getInfo(NICK)
			  + " " + ch.getName()
			  + " " + *it
			  + " " + client->getInfo(NICK)
			  + std::to_string(std::time(NULL)))
			, client);
	}
	this->sendMsg(Msg(this->prefix
		, RPL_ENDOFINVITELIST
		, client->getInfo(NICK)
		  + " " + ch.getName()
		  + " :End of ch invitation list")
		, client);
}

void 		Server::outBanRoll(Channel &ch, Client *client)
{
	std::set<std::string>::iterator it;
	std::set<std::string> &banRoll = ch.getBanRoll();

	it = banRoll.begin();
	for (; it != banRoll.end(); ++it)
	{
		this->sendMsg(Msg(this->prefix
			, RPL_BANLIST
			, client->getInfo(NICK)
			  + " " + ch.getName()
			  + " " + *it
			  + " " + client->getInfo(NICK)
			  + std::to_string(std::time(NULL)))
			, client);
	}
	this->sendMsg(Msg(this->prefix
		, RPL_ENDOFBANLIST
		, client->getInfo(NICK)
		  + " " + ch.getName()
		  + " :End of ch ban list")
		, client);
}



static void setFullMask(std::string &fullMask, const std::string &mask)
{
	std::string defaultString = "*!*@*";

	if (mask.find('!') == std::string::npos)
		fullMask = mask + defaultString.substr(1);
	else if (mask.find('@') == std::string::npos)
		fullMask = mask + defaultString.substr(3);
	else
		fullMask = mask;
}

int			Server::modeHelper(std::string &error, size_t &modeIndex, const Msg &message, Client *client, Client *exceptClient)
{
	bool        isAdd = true;
	char        mode;
	char 		sign;
	size_t      modeParamIndex;
	size_t      modeCharIndex = 0;
	std::string	param;
	std::map<std::string, Client>::iterator		clientIter;
	std::map<std::string, Channel>::iterator 	chanIter;
	std::vector<Client *>						joinedUsers;

	sign = '+';
	if (message.getParameter(modeIndex)[0] == '-')
	{
		isAdd = false;
		sign = '-';
	}
	if (message.getParameter(modeIndex)[0] == '-' || message.getParameter(modeIndex)[0] == '+')
		modeCharIndex += 1;
	mode = message.getParameter(modeIndex)[modeCharIndex];
	modeParamIndex = modeIndex + 1;
	while (mode != 0)
	{
		switch (mode) {
			case 'o':
				if (modeParamIndex >= message.getParameters().size())
				{
					error = ERR_NEEDMOREPARAMS;
					return (-1); //need more params
				}
				clientIter = this->sendClients.find(message.getParameter(modeParamIndex));
				if (clientIter == this->sendClients.end())
				{
					error = ERR_NOSUCHNICK;
					return (-1);
				}
				else if (!clientIter->second.findChannel(message.getParameter(0)))
				{
					error = ERR_USERNOTINCHANNEL;
					return (-1);
				}
				chanIter = this->localChannelRoll.find(message.getParameter(0));
				if (chanIter == this->localChannelRoll.end())
					chanIter = this->remoteChannelRoll.find(message.getParameter(0));
				if (isAdd)
					chanIter->second.makeUserToOper(message.getParameter(modeParamIndex));
				else
					chanIter->second.makeOperToUser(message.getParameter(modeParamIndex));
				joinedUsers = chanIter->second.getUsersRoll(this->serverName);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
				{
					this->sendMsg(Msg(":" + getClientPrefix(client)
						, "MODE"
						, chanIter->second.getName()
						  + " " + sign + "o"
						  + " " + message.getParameter(modeParamIndex)), joinedUsers[i]);
				}
				broadcastMsg(Msg(":" + exceptClient->getInfo(NICK)
					, "MODE"
					, 	 message.getParameter(0)
						  + " " + message.getParameter(1)
						  + " " + message.getParameter(2))
					, exceptClient);
				++modeParamIndex;
				break;

			case 'v':
				if (modeParamIndex >= message.getParameters().size())
				{
					error = ERR_NEEDMOREPARAMS;
					return (-1); //need more params
				}
				clientIter = this->sendClients.find(message.getParameter(modeParamIndex));
				if (clientIter == this->sendClients.end())
				{
					error = ERR_NOSUCHNICK;
					return (-1);
				}
				else if (!clientIter->second.findChannel(message.getParameter(0)))
				{
					error = ERR_USERNOTINCHANNEL;
					return (-1);
				}
				joinedUsers = chanIter->second.getUsersRoll(this->serverName);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
				{
					this->sendMsg(Msg(":" + getClientPrefix(client)
						, "MODE"
						, chanIter->second.getName()
						  + " " + sign + "v"
						  + " " + message.getParameter(modeParamIndex)), joinedUsers[i]);
				}
				broadcastMsg(Msg(":" + exceptClient->getInfo(NICK)
					, "MODE"
					, 	 message.getParameter(0)
						  + " " + message.getParameter(1)
						  + " " + message.getParameter(2))
					, exceptClient);
				++modeParamIndex;
				break;

			case 'k':
				if (isAdd && modeParamIndex >= message.getParameters().size())
				{
					error = ERR_NEEDMOREPARAMS;
					return (-1); //need more params
				}
				chanIter = this->localChannelRoll.find(message.getParameter(0));
				if (chanIter == this->localChannelRoll.end())
					chanIter = this->remoteChannelRoll.find(message.getParameter(0));
				if (isAdd)
					chanIter->second.setKey(message.getParameter(modeParamIndex));
				else
					chanIter->second.clearKey();
				joinedUsers = chanIter->second.getUsersRoll(this->serverName);
				if (modeParamIndex >= message.getParameters().size())
					param = "*";
				else
					param = message.getParameter(modeParamIndex);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
				{
					this->sendMsg(Msg(":" + getClientPrefix(client)
						, "MODE"
						, chanIter->second.getName()
						  + " " + sign + "k"
						  + " " + param), joinedUsers[i]);
				}
				broadcastMsg(Msg(":" + exceptClient->getInfo(NICK)
					, "MODE"
					, 	 message.getParameter(0)
						  + " " + message.getParameter(1)
						  + " " + message.getParameter(2))
					, exceptClient);
				++modeParamIndex;
				break;

			case 'l':
				if (isAdd && modeParamIndex >= message.getParameters().size())
				{
					error = ERR_NEEDMOREPARAMS;
					return (-1); //need more params
				}
				chanIter = this->localChannelRoll.find(message.getParameter(0));
				if (chanIter == this->localChannelRoll.end())
					chanIter = this->remoteChannelRoll.find(message.getParameter(0));
				if (isAdd)
					chanIter->second.setRAnge(message.getParameter(modeParamIndex));
				else
					chanIter->second.clearRAnge();
				joinedUsers = chanIter->second.getUsersRoll(this->serverName);
				if (modeParamIndex >= message.getParameters().size())
					param = "*";
				else
					param = message.getParameter(modeParamIndex);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
				{
					this->sendMsg(Msg(":" + getClientPrefix(client)
						, "MODE"
						, chanIter->second.getName()
						  + " " + sign + "l"
						  + " " + param), joinedUsers[i]);
				}
				broadcastMsg(Msg(":" + exceptClient->getInfo(NICK)
					, "MODE"
					, 	 message.getParameter(0)
						  + " " + message.getParameter(1)
						  + " " + message.getParameter(2))
					, exceptClient);
				++modeParamIndex;
				break;

			case 'b':
				chanIter = this->localChannelRoll.find(message.getParameter(0));
				if (chanIter == this->localChannelRoll.end())
					chanIter = this->remoteChannelRoll.find(message.getParameter(0));
				if (isAdd && exceptClient->getStatus() == USER && modeParamIndex >= message.getParameters().size())
				{
					this->outBanRoll(chanIter->second, client);
					break;
				}
				if (modeParamIndex >= message.getParameters().size())
					param = "*";
				else
					setFullMask(param, message.getParameter(modeParamIndex));
				if (isAdd)
					chanIter->second.setRoll(chanIter->second.getBanRoll(), MODE_B, param);
				else if (!isAdd && modeParamIndex >= message.getParameters().size())
					chanIter->second.clearRoll(chanIter->second.getBanRoll(), MODE_B);
				else
					chanIter->second.eraseElm(chanIter->second.getBanRoll(), MODE_B, param);
				joinedUsers = chanIter->second.getUsersRoll(this->serverName);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
				{
					this->sendMsg(Msg(":" + getClientPrefix(client)
						, "MODE"
						, chanIter->second.getName()
						  + " " + sign + "b"
						  + " " + param), joinedUsers[i]);
				}
				broadcastMsg(Msg(":" + exceptClient->getInfo(NICK)
					, "MODE"
					, 	 message.getParameter(0)
						  + " " + message.getParameter(1)
						  + " " + param)
					, exceptClient);
				++modeParamIndex;
				break;

			case 'e':
				chanIter = this->localChannelRoll.find(message.getParameter(0));
				if (chanIter == this->localChannelRoll.end())
					chanIter = this->remoteChannelRoll.find(message.getParameter(0));
				if (isAdd && exceptClient->getStatus() == USER && modeParamIndex >= message.getParameters().size())
				{
					this->outExceptionRoll(chanIter->second, client);
					break;
				}
				if (modeParamIndex >= message.getParameters().size())
					param = "*";
				else
					setFullMask(param, message.getParameter(modeParamIndex));
				if (isAdd)
					chanIter->second.setRoll(chanIter->second.getExceptionRoll(), MODE_E, param);
				else if (!isAdd && modeParamIndex >= message.getParameters().size())
					chanIter->second.clearRoll(chanIter->second.getExceptionRoll(), MODE_E);
				else
					chanIter->second.eraseElm(chanIter->second.getExceptionRoll(), MODE_E, param);
				joinedUsers = chanIter->second.getUsersRoll(this->serverName);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
				{
					this->sendMsg(Msg(":" + getClientPrefix(client)
						, "MODE"
						, chanIter->second.getName()
						  + " " + sign + "e"
						  + " " + param), joinedUsers[i]);
				}
				broadcastMsg(Msg(":" + exceptClient->getInfo(NICK)
					, "MODE"
					, 	 message.getParameter(0)
						  + " " + message.getParameter(1)
						  + " " + param)
					, exceptClient);
				++modeParamIndex;
				break;

			case 'I':
				chanIter = this->localChannelRoll.find(message.getParameter(0));
				if (chanIter == this->localChannelRoll.end())
					chanIter = this->remoteChannelRoll.find(message.getParameter(0));
				if (isAdd && exceptClient->getStatus() == USER && modeParamIndex >= message.getParameters().size())
				{
					this->outInvitRoll(chanIter->second, client);
					break;
				}
				if (modeParamIndex >= message.getParameters().size())
					param = "*";
				else
					setFullMask(param, message.getParameter(modeParamIndex));
				if (isAdd)
					chanIter->second.setRoll(chanIter->second.getInvitRoll(), MODE_UI, param);
				else if (!isAdd && modeParamIndex >= message.getParameters().size())
					chanIter->second.clearRoll(chanIter->second.getInvitRoll(), MODE_UI);
				else
					chanIter->second.eraseElm(chanIter->second.getInvitRoll(), MODE_UI, param);
				joinedUsers = chanIter->second.getUsersRoll(this->serverName);
				for (int i = 0; i < (int)joinedUsers.size(); i++)
				{
					this->sendMsg(Msg(":" + getClientPrefix(client)
						, "MODE"
						, chanIter->second.getName()
						  + " " + sign + "I"
						  + " " + param), joinedUsers[i]);
				}
				broadcastMsg(Msg(":" + exceptClient->getInfo(NICK)
					, "MODE"
					, 	 message.getParameter(0)
						  + " " + message.getParameter(1)
						  + " " + param)
					, exceptClient);
				++modeParamIndex;
				break;

			default:
				break;
		}
		mode = message.getParameter(modeIndex)[++modeCharIndex];
	}
	return (modeParamIndex + 1);
}

int         Server::modeHandler(const Msg &message, Client *client)
{
	std::string msg;
	std::string check;
	size_t parameterSize;
	std::map<std::string, Channel>::iterator targetChannel;
	std::vector<Client *>						joinedUsers;
	Client *targetClient;

	client->setCurrentCommand("MODE");
	if (client->getStatus() == UNKNOWN)
		return (this->*(this->replies[ERR_NOTREGISTERED]))(message, client);
	else if (client->getStatus() == USER)
		this->infosPerCommand[client->getCurrentCommand()].incrLocalCount(1);
	else
		this->infosPerCommand[client->getCurrentCommand()].incrRemoteCount(1);
	if ((check = client->prefixCheck(message)) != "ok")
		return (this->*(this->replies[check]))(message, client);

	parameterSize = message.getParameters().size();
	if (parameterSize < 2)
		return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);
	targetChannel = this->localChannelRoll.find(message.getParameter(0));
	if (targetChannel == this->localChannelRoll.end())
		targetChannel = this->remoteChannelRoll.find(message.getParameter(0));
	if (targetChannel == this->remoteChannelRoll.end())
	{
		this->sendMsg(Msg(this->prefix, ERR_NOSUCHCHANNEL, client->getInfo(NICK) + " " + message.getParameter(0) + " :No such ch"), client);
		return (CONNECT);
	}


	if (client->getStatus() == USER &&
		(targetClient = targetChannel->second.findOpr(client->getInfo(NICK))) == NULL)
		return (CONNECT); //
	if (client->getStatus() == SERVER &&
		(targetClient = targetChannel->second.findOpr(message.getPrefix().substr(1))) == NULL)
		return (CONNECT); //
	size_t modeIndex = 1;
	size_t modeParamIndex;
	std::string error = "";
	std::string successState = "";
	while (modeIndex < message.getParameters().size())
	{
		if ((modeParamIndex = this->modeHelper(error, modeIndex, message, targetClient, client)) == ERROR)
			return (this->*(this->replies[error]))(message, client);
		error.clear();
		if (targetChannel->second.toggleMode(successState, error, modeIndex, message) == ERROR)
			return (this->*(this->replies[error]))(message, client);
		modeIndex += modeParamIndex;
	}
	if (successState.size() > 1)
	{
		joinedUsers = targetChannel->second.getUsersRoll(this->serverName);
		for (int i = 0; i < (int) joinedUsers.size(); i++) {
			this->sendMsg(Msg(":" + getClientPrefix(targetClient), "MODE",
									  targetChannel->first + " " + successState + " " +
									  targetClient->getInfo(NICK)), joinedUsers[i]);
		}
		if (message.getPrefix().empty()) {
			msg = ":" + client->getInfo(NICK) + " ";
			msg += message.getTotalMsg();
		}
		else
			msg = message.getTotalMsg();
		broadcastMsg(Msg(msg), client);
	}
	return (CONNECT);
}

int     Server::namesHandler(const Msg &message, Client *client)
{
    std::string                                 noChannelUserRoll;
    std::map<std::string, Channel>::iterator    it;
    std::vector<std::string>                    chNames;

    client->setCurrentCommand("NAMES");
    if (!(message.getParameters().size() >= 0 && message.getParameters().size() <= 2))
        return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));
    
    if (message.getParameters().size() == 0)
    {
        it = this->localChannelRoll.begin();
        for (; it != this->localChannelRoll.end(); it++)
            this->sendMsg(Msg(this->prefix, RPL_NAMREPLY, client->getInfo(NICK) + " = " + it->first + " :" + it->second.getUserNameRoll()), client);
        it = this->remoteChannelRoll.begin();
        for (; it != this->remoteChannelRoll.end(); it++)
            this->sendMsg(Msg(this->prefix, RPL_NAMREPLY, client->getInfo(NICK) + " = " + it->first + " :" + it->second.getUserNameRoll()), client);

        strClientPtrIter pit = this->clientRoll.begin();
        for (; pit != this->clientRoll.end(); pit++)
        {   


            if (pit->second->getdigitsOfJoinChannels() == 0)
                noChannelUserRoll += (pit->first + " ");
        }
        if (!noChannelUserRoll.empty())
            this->sendMsg(Msg(this->prefix, RPL_NAMREPLY, client->getInfo(NICK) + " * * :" + noChannelUserRoll), client);

        this->sendMsg(Msg(this->prefix, RPL_ENDOFNAMES, client->getInfo(NICK) + " * :End of NAMES list"), client);
    }
    else if (message.getParameters().size() == 1)
    {
        chNames = getChannelNames(message.getParameter(0));
        for (int i = 0; i < (int)chNames.size(); i++)
        {
            if ((it = this->localChannelRoll.find(chNames[i])) != this->localChannelRoll.end())
                this->sendMsg(Msg(this->prefix, RPL_NAMREPLY, client->getInfo(NICK) + " = " + it->first + " :" + it->second.getUserNameRoll()), client);
            else if ((it = this->remoteChannelRoll.find(chNames[i])) != this->remoteChannelRoll.end())
                this->sendMsg(Msg(this->prefix, RPL_NAMREPLY, client->getInfo(NICK) + " = " + it->first + " :" + it->second.getUserNameRoll()), client);
            this->sendMsg(Msg(this->prefix, RPL_ENDOFNAMES, client->getInfo(NICK) + " " + chNames[i] + " :End of NAMES list"), client);
        }
    }
    else
    {

    }
    return (CONNECT);
}

int     Server::listHandler(const Msg &message, Client *client)
{
    std::map<std::string, Channel>::iterator it;
    std::vector<std::string> chNames;

    client->setCurrentCommand("LIST");
    if (!(message.getParameters().size() >= 0 && message.getParameters().size() <= 2))
        return ((this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client));


    this->sendMsg(Msg(this->prefix, RPL_LISTSTART, client->getInfo(NICK) + " Channel :Users  Names"), client);

    if (message.getParameters().size() == 0)
    {
        it = this->localChannelRoll.begin();
        for (; it != this->localChannelRoll.end(); it++)
            this->sendMsg(Msg(this->prefix, RPL_LIST, client->getInfo(NICK) + " " + it->first + " " + std::to_string(it->second.getdigitsOfUsers()) + " :" + it->second.getSec()), client);
        it = this->remoteChannelRoll.begin();
        for (; it != this->remoteChannelRoll.end(); it++)
            this->sendMsg(Msg(this->prefix, RPL_LIST, client->getInfo(NICK) + " " + it->first + " " + std::to_string(it->second.getdigitsOfUsers()) + " :" + it->second.getSec()), client);
        this->sendMsg(Msg(this->prefix, RPL_LIST, client->getInfo(NICK) + " &SERVER 0 :Server Msgs"), client);
    }
    else if (message.getParameters().size() == 1)
    {
        chNames = getChannelNames(message.getParameter(0));
        for (int i = 0; i < (int)chNames.size(); i++)
        {
            if ((it = this->localChannelRoll.find(chNames[i])) != this->localChannelRoll.end())
                this->sendMsg(Msg(this->prefix, RPL_LIST, client->getInfo(NICK) + " " + it->first + " " + std::to_string(it->second.getdigitsOfUsers()) + " :" + it->second.getSec()), client);
            else if ((it = this->remoteChannelRoll.find(chNames[i])) != this->remoteChannelRoll.end())
                this->sendMsg(Msg(this->prefix, RPL_LIST, client->getInfo(NICK) + " " + it->first + " " + std::to_string(it->second.getdigitsOfUsers()) + " :" + it->second.getSec()), client);
        }
    }


    this->sendMsg(Msg(this->prefix, RPL_LISTEND, client->getInfo(NICK) + " :End of LIST"), client);
    return (CONNECT);
}

int     Server::inviteHandler(const Msg &message, Client *client)
{
    Client      *targetUser;
    Channel     *targetChannel;
    std::string prefix;
    
    if (message.getParameters().size() != 2)
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);


    if (this->sendClients.find(message.getParameter(0)) != this->sendClients.end())
        targetUser = &this->sendClients[message.getParameter(0)];
    else
        return (this->*(this->replies[ERR_NOSUCHNICK]))(message, client);   // 401

    if (this->localChannelRoll.find(message.getParameter(1)) != this->localChannelRoll.end())
        targetChannel = &this->localChannelRoll[message.getParameter(1)];
    else if (this->remoteChannelRoll.find(message.getParameter(1)) != this-> remoteChannelRoll.end())
        targetChannel = &this->remoteChannelRoll[message.getParameter(1)];
    else
    {
        this->sendMsg(Msg(this->prefix, ERR_NOSUCHCHANNEL, client->getInfo(NICK) + " " + message.getParameter(1) + " :No such ch"), client);
        return (CONNECT);
    }

    if (client->getStatus() == USER && !client->findChannel(message.getParameter(1)))
    {
        this->sendMsg(Msg(this->prefix, ERR_NOTONCHANNEL, client->getInfo(NICK) + " " + message.getParameter(1) + " :You are not on that ch"), client);
        return (CONNECT);
    }

    if (client->getStatus() == USER && !targetChannel->findOpr(client->getInfo(NICK)))
    {
        this->sendMsg(Msg(this->prefix, ERR_CHANOPRIVSNEEDED, client->getInfo(NICK) + " " + message.getParameter(1) + " :You're not ch operator"), client);
        return (CONNECT);
    }

    if (targetChannel->findJoinUser(message.getParameter(0)))
    {
        this->sendMsg(Msg(this->prefix, ERR_USERONCHANNEL, message.getParameter(0) + " " + message.getParameter(1) + " :is already on ch"), client);
        return (CONNECT);
    }        

    if (this->clientRoll.find(message.getParameter(0)) != this->clientRoll.end())
    {   

        targetUser->addInvitedChannel(message.getParameter(1));
        prefix = getClientPrefix(&this->sendClients[message.getPrefix().substr(1)]);
        this->sendMsg(Msg(":" + prefix, "INVITE", targetUser->getInfo(NICK) + " " + message.getParameter(1)), targetUser);
        prefix = getClientPrefix(targetUser);
        this->sendMsg(Msg(":" + prefix, RPL_INVITING, message.getPrefix().substr(1) + " " + message.getParameter(0) + " " + message.getParameter(1)), &this->sendClients[message.getPrefix().substr(1)]);
    }

    else
    {
        if (message.getPrefix().empty())
            prefix = client->getInfo(NICK);
        else
            prefix = message.getPrefix().substr(1);
        this->sendMsg(Msg(":" + prefix, "INVITE", message.getParameter(0) +  " " + message.getParameter(1)), targetUser);
    }
    return (CONNECT);
}

int         Server::kickHandler(const Msg &message, Client *client)
{
    Channel                 *targetChannel;
    Client                  *targetUser;
    std::string             prefix;
    std::string             kickMsg;
    std::vector<Client *>   joinedUsers;

    if (!(message.getParameters().size() >= 2 && message.getParameters().size() <= 3))
        return (this->*(this->replies[ERR_NEEDMOREPARAMS]))(message, client);

    if (this->localChannelRoll.find(message.getParameter(0)) != this->localChannelRoll.end())
        targetChannel = &this->localChannelRoll[message.getParameter(0)];
    else if (this->remoteChannelRoll.find(message.getParameter(0)) != this->remoteChannelRoll.end())
        targetChannel = &this->remoteChannelRoll[message.getParameter(0)];
    else
    {
        this->sendMsg(Msg(this->prefix, ERR_NOSUCHCHANNEL, client->getInfo(NICK) + " " + message.getParameter(0) + " :No such ch"), client);
        return (CONNECT);
    }

    if (this->sendClients.find(message.getParameter(1)) != this->sendClients.end())
        targetUser = &this->sendClients[message.getParameter(1)];
    else
    {
        this->sendMsg(Msg(this->prefix, ERR_NOSUCHNICK, client->getInfo(NICK) + " " + message.getParameter(1) + " :No such nick or ch name"), client);
        return (CONNECT);
    }

    if (client->getStatus() == USER && !(targetChannel->findJoinUser(client->getInfo(NICK)) || targetChannel->findOpr(client->getInfo(NICK))))
    {
        this->sendMsg(Msg(this->prefix, ERR_NOTONCHANNEL, client->getInfo(NICK) + " " + message.getParameter(0) + " :You are not on that ch"), client);
        return (CONNECT);
    }

    if (client->getStatus() == USER && !targetChannel->findOpr(client->getInfo(NICK)))
    {
        this->sendMsg(Msg(this->prefix, ERR_CHANOPRIVSNEEDED, client->getInfo(NICK) + " " + message.getParameter(0) + " :You're not ch operator"), client);
        return (CONNECT);
    }

    if (!(targetChannel->findOpr(message.getParameter(1)) || targetChannel->findJoinUser(message.getParameter(1))))
    {
        this->sendMsg(Msg(this->prefix, ERR_USERNOTINCHANNEL, message.getParameter(1) + " " + message.getParameter(0) + " :They aren't on that ch"), client);
        return (CONNECT);
    }

    
    if (message.getPrefix().empty())
        prefix = client->getInfo(NICK);
    else
        prefix = message.getPrefix().substr(1);
    if (message.getParameters().size() > 2)
        kickMsg = message.getParameter(2);
    else
        kickMsg = ":" + prefix;

    joinedUsers = targetChannel->getUsersRoll(this->serverName);
    for (int i = 0; i < (int)joinedUsers.size(); i++)
        this->sendMsg(Msg(":"+getClientPrefix(&this->sendClients[prefix])
                                    , "KICK"
                                    , message.getParameter(0)
                                    + " " + message.getParameter(1)
                                    + " " + kickMsg)
                                    , joinedUsers[i]);

    targetChannel->leaveUser(targetUser);
    targetUser->leaveChannel(message.getParameter(0));

    this->broadcastMsg(Msg(":" + prefix
                                    , "KICK"
                                    , message.getParameter(0)
                                    + " " + message.getParameter(1)
                                    + " " + kickMsg), client);
    

    return (CONNECT);
}