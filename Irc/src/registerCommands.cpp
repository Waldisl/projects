#include "Server.hpp"

void	Server::registerCommands(void)
{
	this->commands["PASS"] = &Server::passHandler;
	this->commands["NICK"] = &Server::nickHandler;
	this->commands["USER"] = &Server::userHandler;
	this->commands["SERVER"] = &Server::serverHandler;
	this->commands["SQUIT"] = &Server::squitHandler;
	this->commands["WALLOPS"] = &Server::wallopsHandler;

	this->commands["VERSION"] = &Server::versionHandler;
	this->commands[RPL_VERSION] = &Server::rReplyHandler;
	
	this->commands["STATS"] = &Server::statsHandler;
	this->commands[RPL_STATSLINKINFO] = &Server::rReplyHandler;
	this->commands[RPL_STATSCOMMANDS] = &Server::rReplyHandler;
	this->commands[RPL_STATSUPTIME] = &Server::rReplyHandler;
	this->commands[RPL_ENDOFSTATS] = &Server::rReplyHandler;

	this->commands["LINKS"] = &Server::linksHandler;

	this->commands["QUIT"] = &Server::quitHandler;

	this->commands["TIME"] = &Server::timeHandler;
	this->commands[RPL_TIME] = &Server::rReplyHandler;

	this->commands["CONNECT"] = &Server::connectHandler;

	this->commands["TRACE"] = &Server::traceHandler;
	this->commands[RPL_TRACELINK] = &Server::rReplyHandler;
	this->commands[RPL_TRACESERVER] = &Server::rReplyHandler;
	this->commands[RPL_TRACEEND] = &Server::rReplyHandler;


	this->commands["PRIVMSG"] = &Server::privmsgHandler;
	this->commands["NOTICE"] = &Server::noticeHandler;

	this->commands["JOIN"] = &Server::joinHandler;
	this->commands["PART"] = &Server::partHandler;
	this->commands["TOPIC"] = &Server::topicHandler;
	this->commands["NAMES"] = &Server::namesHandler;
	this->commands["LIST"] = &Server::listHandler;
	this->commands["INVITE"] = &Server::inviteHandler;
	this->commands["KICK"] = &Server::kickHandler;

	this->commands["ADMIN"] = &Server::adminHandler;
	this->commands[RPL_ADMINME] = &Server::rReplyHandler;
    this->commands[RPL_ADMINLOC1] = &Server::rReplyHandler;
    this->commands[RPL_ADMINLOC2] = &Server::rReplyHandler;
    this->commands[RPL_ADMINEMAIL] = &Server::rReplyHandler;

    this->commands["INFO"] = &Server::infoHandler;
    this->commands[RPL_INFO] = &Server::rReplyHandler;
    this->commands[RPL_ENDOFINFO] = &Server::rReplyHandler;
	
	// 341
	this->commands[RPL_INVITING] = &Server::rInviting;

	// ?????????
    this->commands["SHOW"] = &Server::out;
    this->commands["PING"] = &Server::pingHandler;
    this->commands["PONG"] = &Server::pongHandler;

    this->commands["MODE"] = &Server::modeHandler;
}
