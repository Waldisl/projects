#include "Server.hpp"

void 	Server::sendChannelRolls(Client *client)
{
	std::string 			prefix;
	std::string 			parameters;
	std::vector<Client *>	userRoll;
	std::vector<Client *>::iterator userIter;
	std::map<std::string, Client *>::iterator operIter;
	std::map<std::string, Channel>::iterator mapIter = this->localChannelRoll.begin();

	for (; mapIter != this->localChannelRoll.end(); ++mapIter)
	{
		if (mapIter->first[0] == '#')
		{
			std::map<std::string, Client *> &operRoll = mapIter->second.Oprs();
			userRoll = mapIter->second.getUsersRoll("all");
			userIter = userRoll.begin();
			for (; userIter != userRoll.end(); ++userIter) {
				this->sendMsg(Msg(":" + (*userIter)->getInfo(NICK), "JOIN", mapIter->first), client);
			}
			operIter = operRoll.begin();
			prefix = ":" + operIter->second->getInfo(NICK);
			parameters = "";
			for (; operIter != operRoll.end(); ++operIter)
				parameters += operIter->second->getInfo(NICK) + " ";
			this->sendMsg(Msg(prefix, "MODE", mapIter->first + " +o " + parameters), client);
			userRoll.clear();
		}
	}
	mapIter = this->remoteChannelRoll.begin();
	for (; mapIter != this->remoteChannelRoll.end(); ++mapIter)
	{
		std::map<std::string, Client *> &operRoll = mapIter->second.Oprs();
		userRoll = mapIter->second.getUsersRoll("all");
		userIter = userRoll.begin();
		for (; userIter != userRoll.end(); ++userIter) {
			this->sendMsg(Msg(":" + (*userIter)->getInfo(NICK), "JOIN", mapIter->first), client);
		}
		operIter = operRoll.begin();
		prefix = ":" + operIter->second->getInfo(NICK);
		parameters = "";
		for (; operIter != operRoll.end(); ++operIter)
			parameters += operIter->second->getInfo(NICK) + " ";
		this->sendMsg(Msg(prefix, "MODE", mapIter->first + " +o " + parameters), client);
		userRoll.clear();
	}
}
