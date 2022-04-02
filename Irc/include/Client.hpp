#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "utils.hpp"
#include "Replies.hpp"
#include "Channel.hpp"

class Channel;

enum ClientStatus
{
	UNKNOWN,
	SERVER,
	USER,
	SERVICE
};

enum UserIndex
{
	HOSTNAME,
	NICK,
	ADDRESS,
	USERNAME,
	REALNAME,
	USERMODE
};

enum ServerIndex
{
	UPLINKSERVER,
	SERVERNAME,
	HOPCOUNT,
	SERVERINFO,
	TOKEN,
};

enum QueryData
{
	SENDQUEUE,
	SENDMSG,
	SENDBYTES,
	RECVMSG,
	RECVBYTES,
};


class Client
{
private:
	int 								fd;
	bool								isAuthorized;

	ClientStatus 						status;
	std::string							receivedMsgStr;
	std::vector<std::string> 			info;
	std::vector<size_t> 				queryData;

	std::string			currentCommand;
	std::string			prevCommand;

	std::time_t			startTime;
	bool                waitPong;
	std::time_t         lastPing;
	std::time_t         pingRAnge;

	std::map<std::string, Channel *>	subscribedChannels;
	std::set<std::string>				invitedChannelRoll;

public:
	Client(void);
	Client(const int fd, const bool isAuthorized = false);
	~Client(void);
	Client &operator=(const Client &client);
	const int &getFd(void) const;
	const ClientStatus &getStatus(void) const;
	void setStatus(const ClientStatus &status);
	const bool &getIsAuthorized(void) const;
	void setIsAuthorized(bool isAuthorized);
	void setInfo(const int &index, const std::string &myPrefix);
	std::string		getReceivedMsgStr() const;
	void			addReceivedMsgStr(char buffer);
	void			clearReceivedMsgStr(void);

	const std::string &getInfo(const int &index) const;
	const std::vector<std::string> &getInfo(void) const;

	void incrQueryData(const int &index, const int &val);
	std::string getQueryData(const int &index) const;

	std::time_t	getStartTime(void) const;
	void        setLastPing(const std::time_t current);
	std::time_t getLastPing(void) const;

	void        setWaitPong(bool state);
	bool        getWaitPong(void) const;

	void        setPingRAnge(const std::time_t current);
	std::time_t getPingRAnge() const;

	std::string prefixCheck(const Msg &message);

	void				setCurrentCommand(const std::string &command);
	const std::string	&getCurrentCommand(void) const;
	const std::string	&getPrevCommand(void) const;
	void								joinChannel(Channel *ch, const std::string &chName);
	void								leaveChannel(const std::string &chName);

	Channel*							findChannel(const std::string &chName);

	int									getdigitsOfJoinChannels(void);

	void								addInvitedChannel(const std::string &chName);


	void								outChannel(void);
	//
	bool 								isInvited(const std::string &chName);
	void 								setInviteChanRoll(const std::string &chName);

	void 								delInviteChanRoll(const std::string &chName);
	std::vector<std::string>			*getSubscribedChannelRoll(void);
};

#endif
