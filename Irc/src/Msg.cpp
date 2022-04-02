#include "Msg.hpp"



Msg::Msg(void) {}

Msg::Msg(const std::string &message)
{
	std::string::const_iterator		messageIterator;
	messageIterator = message.begin();
	if (*messageIterator == ':')
		this->setString(this->prefix, messageIterator, message);
	this->setString(this->command, messageIterator, message);
	this->toUpper(this->command);
	this->setTotalMsg(this->prefix, this->command, this->getParameterStr(messageIterator, message));
	this->setParameters(messageIterator, message);
}

Msg::Msg(const std::string &prefix, const std::string &command, const std::string &parameters)
 : prefix(prefix), command(this->toUpper(command))
{
	std::string	tmpParameters;
	std::string::const_iterator	iterator;

	tmpParameters = parameters;
	tmpParameters += CR_LF;
	iterator = tmpParameters.begin();
	this->setTotalMsg(prefix, this->command, parameters);
	this->setParameters(iterator, tmpParameters);
}

Msg::~Msg(void)
{
}

std::string					Msg::getParameterStr(std::string::const_iterator iterator, const std::string &message)
{
	std::string			returnStr;

	returnStr = std::string("");
	for(; iterator != message.end(); ++iterator)
	{
		if (*iterator == '\r' || *iterator == '\n')
			break ;
		returnStr += *iterator;
	}
	return (returnStr);
}

void						Msg::toUpper(std::string &command)
{
	for(size_t i = 0; i < command.size(); i++)
	{
		if ('a' <= command[i] && command[i] <= 'z')
			command[i] = command[i] - 32;
		else
			command[i] = command[i];
	}
}

std::string					Msg::toUpper(const std::string &command)
{
	std::string		returnString;

	returnString = std::string("");
	for(size_t i = 0; i < command.size(); i++)
	{
		if ('a' <= command[i] && command[i] <= 'z')
			returnString += command[i] - 32;
		else
			returnString += command[i];
	}
	return (returnString);
}

Msg						&Msg::operator=(const Msg &message)
{
	this->totalMsg = message.totalMsg;
	this->prefix = message.prefix;
	this->command = message.command;
	this->parameters.resize(message.parameters.size());
	std::copy(message.parameters.begin(), message.parameters.end(), this->parameters.begin());
	return (*this);
}

void						Msg::skipSpace(std::string::const_iterator &iterator, const std::string &message)
{
	while (*iterator == ' ' && iterator != message.end())
		++iterator;
}

void						Msg::setTotalMsg(const std::string &prefix, const std::string &command, const std::string &parameters)
{
	this->totalMsg = "";
	this->totalMsg += prefix;
	if (prefix != "")
		this->totalMsg += " ";
	this->totalMsg += command;
	if (parameters != "")
		this->totalMsg += " ";
	this->totalMsg += parameters;
	this->totalMsg += CR_LF;
}

void						Msg::setString(std::string &target, std::string::const_iterator &iterator, const std::string &message)
{
	target = "";
	while (*iterator != ' ' && *iterator != '\r' && *iterator != '\n' && iterator != message.end())
	{
		target += *iterator;
		++iterator;
	}
	this->skipSpace(iterator, message);
}

void						Msg::setParameters(std::string::const_iterator &iterator, const std::string &message)
{
	std::string parameter;

	while (*iterator != '\r' && *iterator != '\n')
	{
		if (*iterator == ':')
		{
			parameter = "";
			while (*iterator != '\r' && *iterator != '\n' && iterator != message.end())
			{
				parameter += *iterator;
				++iterator;
			}
			this->setVector(this->parameters, parameter);
		}
		else
		{
			this->setString(parameter, iterator, message);
			this->setVector(this->parameters, parameter);
		}
	}
}

void						Msg::setVector(std::vector<std::string> &vector, std::string &parameter)
{
	vector.push_back(parameter);
	parameter = "";
}

const std::string			Msg::getPrefix(void) const
{
	return (this->prefix);
}

const std::string			Msg::getCommand(void) const
{
	return (this->command);
}

const std::string			Msg::getParameter(const int &index) const
{
	return (this->parameters[index]);
}

std::vector<std::string>	Msg::getParameters(void) const
{
	return (this->parameters);
}

const std::string			&Msg::getTotalMsg(void) const
{
	return (this->totalMsg);
}
