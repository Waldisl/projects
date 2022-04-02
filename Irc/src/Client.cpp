#include "Client.hpp"

Client::Client()
	: fd(0), isAuthorized(false), status(UNKNOWN), receivedMsgStr("")
	, currentCommand(""), prevCommand(""), waitPong(true)
{
	this->info.assign(DEFAULT_SIZE, "");
	this->queryData.assign(5, 0);
	this->startTime = std::time(NULL);
	this->lastPing = this->startTime;
}
Client::Client(const int fd, const bool isAuthorized)
	: fd(fd), isAuthorized(isAuthorized), status(UNKNOWN), receivedMsgStr("")
	, currentCommand(""), prevCommand(""), waitPong(true)
{
	this->info.assign(DEFAULT_SIZE, "");
	this->queryData.assign(5, 0);
	this->startTime = std::time(NULL);
	this->lastPing = this->startTime;
}
Client::~Client(void)
{
}

Client						&Client::operator=(const Client &client)
{
	this->fd = client.fd;
	this->isAuthorized = client.isAuthorized;
	this->status = client.status;
	this->info.resize(client.info.size());
	std::copy(client.info.begin(), client.info.end(), this->info.begin());
	return (*this);
}

const int &Client::getFd(void) const
{
	return (this->fd);
}

const ClientStatus &Client::getStatus(void) const
{
	return (this->status);
}

void Client::setStatus(const ClientStatus &status)
{
	this->status = status;
}

const bool &Client::getIsAuthorized(void) const
{
	return (this->isAuthorized);
}

std::string	Client::getReceivedMsgStr(void) const
{
	return (this->receivedMsgStr);
}

void		Client::addReceivedMsgStr(char buffer)
{
	this->receivedMsgStr += buffer;
}

void		Client::clearReceivedMsgStr(void)
{
	this->receivedMsgStr.clear();
}

void Client::setIsAuthorized(bool isAuthorized)
{
	this->isAuthorized = isAuthorized;
}

void Client::setInfo(const int &index, const std::string &value)
{
	this->info[index] = value;
}

const std::string &Client::getInfo(const int &index) const
{
	return (this->info[index]);
}

const std::vector<std::string> &Client::getInfo(void) const
{
	return (this->info);
}

void Client::incrQueryData(const int &index, const int &val)
{
	this->queryData[index] += val;
}

std::string Client::getQueryData(const int &index) const
{
	return (std::to_string(this->queryData[index]));
}

std::time_t	Client::getStartTime(void) const
{
	return (this->startTime);
}

void        Client::setLastPing(const std::time_t current)
{
    this->lastPing = current;
}

std::time_t Client::getLastPing() const
{
    return (std::difftime(std::time(NULL), this->lastPing));
}

void    Client::setWaitPong(bool state)
{
    this->waitPong = state;
}

bool    Client::getWaitPong(void) const
{
    return (this->waitPong);
}

void    Client::setPingRAnge(const std::time_t current)
{
    this->pingRAnge = current;
}

std::time_t Client::getPingRAnge() const
{
    return (std::difftime(std::time(NULL), this->pingRAnge));
}

std::string	Client::prefixCheck(const Msg &message)
{
	std::string ret;

	if (this->status == USER)
	{
		if (!message.getPrefix().empty())
			return (ERR_UNKNOWNCOMMAND);
	}
	else if (this->status == SERVER)
	{
	    if (message.getCommand() == "PING")
	        return ("ok");
		if (message.getPrefix().empty())
			return (ERR_NEEDMOREPARAMS);
	}
	return ("ok");
}

void				Client::setCurrentCommand(const std::string &command)
{
	if (this->currentCommand != "")
		this->prevCommand = this->currentCommand;
	this->currentCommand = command;
}
const std::string	&Client::getCurrentCommand(void) const
{
	return (this->currentCommand);
}

const std::string	&Client::getPrevCommand(void) const
{
	return (this->prevCommand);
}

void	Client::joinChannel(Channel *ch, const std::string &chName)
{
	this->subscribedChannels[chName] = ch;
}

void	Client::leaveChannel(const std::string &chName)
{
	this->subscribedChannels.erase(chName);
}

Channel*	Client::findChannel(const std::string &fullChannelName)
{
	if (this->subscribedChannels.find(fullChannelName) != this->subscribedChannels.end())
		return (this->subscribedChannels[fullChannelName]);
	else
		return (nullptr);
}

int			Client::getdigitsOfJoinChannels(void)
{
	return (this->subscribedChannels.size());
}

void	Client::addInvitedChannel(const std::string &chName)
{
	this->invitedChannelRoll.insert(chName);
}

void	Client::outChannel(void)
{
	std::map<std::string, Channel *>::iterator it = this->subscribedChannels.begin();
	std::cout << "[ ";
	for (; it != this->subscribedChannels.end(); it++)
		std::cout << it->second->getName() << " ";
	std::cout << "] " << std::endl;
}

bool 	Client::isInvited(const std::string &chName)
{
	return  (this->invitedChannelRoll.count(chName) ? true : false);
}

void 	Client::setInviteChanRoll(const std::string &chName)
{
	this->invitedChannelRoll.insert(chName);
}

void 	Client::delInviteChanRoll(const std::string &chName)
{
	this->invitedChannelRoll.erase(chName);
}

std::vector<std::string>	*Client::getSubscribedChannelRoll(void)
{
	if (this->subscribedChannels.empty())
		return (NULL);
	std::map<std::string, Channel*>::iterator it = this->subscribedChannels.begin();
	std::vector<std::string> *subscribedChannelRoll = new std::vector<std::string>();

	for (; it != this->subscribedChannels.end(); ++it)
	{
		subscribedChannelRoll->push_back(it->first);
	}
	return (subscribedChannelRoll);
}