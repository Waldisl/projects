#ifndef SERVER_HPP
# define SERVER_HPP

# include "utils.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Msg.hpp"
# include "Replies.hpp"
# include <openssl/ssl.h>
# include <openssl/err.h>

class																	Server
{
public:
	typedef std::map<int, Client>::iterator clientIter;
	typedef std::map<std::string, Client>::iterator strClientIter;
	typedef std::map<std::string, Client*>::iterator strClientPtrIter;
private:
	class Info
	{
	private:
		size_t															bytes;
		size_t															remoteCount;
		size_t															localCount;
		std::string														cmd;
	public:
																			Info();
																			~Info();
		void															incrBytes(const int &size);
		std::string													getBytes() const;
		void															incrRemoteCount(const int &size);
		std::string													getRemoteCount() const;
		void															incrLocalCount(const int &size);
		std::string													getLocalCount() const;
	};

	std::vector<std::string>											cmd;

	std::string															prefix;

	std::string															ipAddress;
	std::string															serverName;
	std::string															version;
	std::string															userMode;
	std::string															chMode;
	std::string															motdDir;

	std::string															pass;
	std::string															info;
	const char															*port;
	std::string 														tlsPort;
	int																	mainSocket;
	int 																tlsMainSocket;
	int																	maxFd;

	fd_set																readFds;

	std::map<int, Client>												acceptClients;
	std::map<std::string, Client>										sendClients;
	std::map<std::string, Client *>										serverRoll;
	std::map<std::string, Client *>										clientRoll;
	std::map<std::string, Client *>										serviceRoll;
	std::map<std::string, Channel>										localChannelRoll;
	std::map<std::string, Channel>										remoteChannelRoll;

	bool																run;

	std::string                                                         adminLoc1;
	std::string                                                         adminLoc2;
	std::string                                                         adminEmail;
	std::time_t															startTime;

	std::map<std::string, Info>											infosPerCommand;

	time_t                                                              pingTime;
	bool                                                                isDeletedClient;
	SSL_CTX																*ctx;
	SSL																	*ssl;
	bool																isSSL;
	int																	sslFd;


	SSL_CTX																*InitCTX(void);
	void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile, bool serv);

	std::map<std::string, int (Server::*)(const Msg &, Client *)>	commands;
	void																registerCommands(void);
	int																	passHandler(const Msg &message, Client *client);
	int																	setLocalNick(const Msg &message, Client *client);
	int																	resetLocalNick(const Msg &message, Client *client);
	int																	localNickHandler(const Msg &message, Client *client);
	int																	setRemoteNick(const Msg &message, Client *client);
	int																	resetRemoteNick(const Msg &message, Client *client);
	int																	remoteNickHandler(const Msg &message, Client *client);
	int																	nickHandler(const Msg &message, Client *client);
	int																	setLocalUser(const Msg &message, Client *client);
	int																	setRemoteUser(const Msg &message, Client *client);
	int																	userHandler(const Msg &message, Client *client);
	int																	localQuitHandler(const Msg &message, Client *client);
	int																	remoteQuitHandler(const Msg &message, Client *client);
	int																	quitHandler(const Msg &message, Client *client);
	int																	serverHandler(const Msg &message, Client *client);
	int																	squitHandler(const Msg &message, Client *client);
	int																	wallopsHandler(const Msg &message, Client *client);
	int																	versionHandler(const Msg &message, Client *client);
	int																	statsHandler(const Msg &message, Client *client);
	int																	linksHandler(const Msg &message, Client *client);
	int																	timeHandler(const Msg &message, Client *client);
	int																	connectHandler(const Msg &message, Client *client);

	int																	traceHandler(const Msg &message, Client *client);
	int																	privmsgHandler(const Msg &message, Client *client);
	int 																noticeHandler(const Msg &message, Client *client);

	int     															joinHandler(const Msg &message, Client *client);
	int     															partHandler(const Msg &message, Client *client);
	int     															topicHandler(const Msg &message, Client *client);
	int                                                                 modeHandler(const Msg &message, Client *client);
	int 																modeHelper(std::string &error, size_t &modeIndex, const Msg &message, Client *client, Client *exceptClient);
	void																outBanRoll(Channel &ch, Client *client);
	void																outExceptionRoll(Channel &ch, Client *client);
	void 																outInvitRoll(Channel &ch, Client *client);

	int     															namesHandler(const Msg &message, Client *client);
	int     															listHandler(const Msg &message, Client *client);
	int     															inviteHandler(const Msg &message, Client *client);
	int         														kickHandler(const Msg &message, Client *client);

	int                                                                 adminHandler(const Msg &message, Client *client);

	int                                                                 infoHandler(const Msg &message, Client *client);

	int                                                                 pingHandler(const Msg &message, Client *client);
  	int                                                                 pongHandler(const Msg &message, Client *client);

	std::map<std::string, int (Server::*)(const Msg &, Client *)>	replies;
	void																registerReplies(void);
	int																	eNoNickNameGivenHandler(const Msg &message, Client *client);
	int																	eNeedMoreParamsHandler(const Msg &message, Client *client);
	int																	eErroneusNickNameHandler(const Msg &message, Client *client);
	int																	eNickNameInUseHandler(const Msg &message, Client *client);
	int																	eAlreadyRegisteredHandler(const Msg &message, Client *client);
	int																	ePassUnauthorizedHandler(const Msg &message, Client *client);
	int																	eErroneusUserNameHandler(const Msg &message, Client *client);
	int																	ePrefixHandler(const Msg &message, Client *client);
	int																	eNickCollisionHandler(const Msg &message, Client *client);
	int																	eCantKillServerHandler(const Msg &message, Client *client);
	int																	eNoSuchServer(const Msg &message, Client *client);
	int																	eUnknownCommand(const Msg &message, Client *client);
	int																	eNotRegistered(const Msg &message, Client *client);
	int																	eNoRecipients(const Msg &message, Client *client);
	int																	eNoTextToSend(const Msg &message, Client *client);
	int																	eNoSuchNick(const Msg &message, Client *client);
	int                                                                 eNoOrigin(const Msg &message, Client *client);
	int 																eUnknownMode(const Msg &message, Client *client);
	int																	eUserNotInChannel(const Msg &message, Client *client);
	int 																eBadChannelKey(const Msg &message, Client *client);
	int																	eInviteOnlyChan(const Msg &message, Client *client);
	int																	eBannedFromChan(const Msg &message, Client *client);

	int																	rRegisterUserHandler(const Msg &message, Client *client);
	int																	rWelcomeMsgHandler(const Msg &message, Client *client);
	int																	rWelcomeHandler(const Msg &message, Client *client);
	int																	rYourHostHandler(const Msg &message, Client *client);
	int																	rCreatedHandler(const Msg &message, Client *client);
	int																	rMyInfoHandler(const Msg &message, Client *client);
	int																	rLUserClientHandler(const Msg &message, Client *client);
	int																	rLUserChannelHandler(const Msg &message, Client *client);
	int																	rLUserMeHandler(const Msg &message, Client *client);
	int																	rMOTDHandler(const Msg &message, Client *client);
	int																	rMOTDContentHandler(const Msg &message, Client *client);
	int																	rMOTDStartHandler(const Msg &message, Client *client);
	int																	rEndOfMOTDHandler(const Msg &message, Client *client);
	int																	rNickHandler(const Msg &message, Client *client);
	int																	rNickBroadcastHandler(const Msg &message, Client *client);
	int																	rUserBroadcastHandler(const Msg &message, Client *client);
	int																	rUserModeBroadcastHandler(const Msg &message, Client *client);
	int																	rPassHandler(const Msg &message, Client *client);
	int																	rServerHandler(const Msg &message, Client *client);
	int																	rHostHandler(const Msg &message, Client *client);
	int																	rOtherServerHandler(const Msg &message, Client *client);
	int																	rServerBroadcastHandler(const Msg &message, Client *client);
	int																	rKillHandler(const Msg &message, Client *client);
	int																	rSquitBroadcastHandler(const Msg &message, Client *client);
	int																	rQuitBroadcastHandler(const Msg &message, Client *client);
	int																	rQuitHandler(const Msg &message, Client *client);
	int																	rInviting(const Msg &message, Client *client);

	int																	rReplyHandler(const Msg &message, Client *client);

	int																	rStatsL(const Msg &message, Client *client);
	int																	rStatsM(const Msg &message, Client *client);
	int																	rStatsO(const Msg &message, Client *client);
	int																	rStatsU(const Msg &message, Client *client);
	int																	rEndOfStats(const Msg &message, Client *client);

	int																	rEndOfLinks(const Msg &message, Client *client);

	void																renewFd(const int fd);

	void																getChildServer(std::list<std::string> &serverRoll, std::string key);
	std::string															getParentServer(std::string key);

	void																connectClient(const int &listenFd);
	void																discntClient(const Msg &message, Client *client);
	void																discntChild(const Msg &message, Client *client);
	void																clearClient(void);
	void																deleteSubServers(const std::string &targetServer, const std::string &info);

	void																receiveMsg(const int &fd);
	void																sendMsg(const Msg &message, Client *client);
	void																broadcastMsg(const Msg &message, Client *client);
	void																settingClient(const Msg &message, Client *client);
	std::vector<std::string>											*getInfoFromWildcard(const std::string &info);

	void																initInfosPerCommand(void);
	void																incrLocalByte(Client *client, const Msg &message);
	void																incrRemoteByte(Client *client, const Msg &message);

	Client																*hasTarget(const std::string &target, strClientPtrIter start, strClientPtrIter end);

	std::string     													getClientPrefix(Client *client);

	void 																sendChannelRolls(Client *client);

	int																	out(const Msg &message, Client *client);
public:
																		Server(const char *pass, const char *port);
																		~Server(void);
	void																init(const char *port);
	void																start(void);
	void																connectServer(const std::string address);

	class GetAddressFailException: public std::exception
	{
		virtual const char* what() const throw();
	};
	class SocketOpenFailException: public std::exception
	{
		virtual const char* what() const throw();
	};
	class SocketBindFailException: public std::exception
	{
		virtual const char* what() const throw();
	};
	class SocketRollenFailException: public std::exception
	{
		virtual const char* what() const throw();
	};
	class SelectFailException: public std::exception
	{
		virtual const char* what() const throw();
	};
	class AcceptFailException: public std::exception
	{
		virtual const char* what() const throw();
	};
};

#endif
