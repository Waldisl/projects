#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "utils.hpp"

class							Msg
{
private:
	std::string						totalMsg;
	std::string						prefix;
	std::string						command;
	std::vector<std::string>		parameters;
	void							skipSpace(std::string::const_iterator &iterator, const std::string &message);
	void							setString(std::string &target, std::string::const_iterator &iterator, const std::string &message);
	void							setParameters(std::string::const_iterator &iterator, const std::string &message);
	void							setVector(std::vector<std::string> &vector, std::string &parameter);
	void							setTotalMsg(const std::string &prefix, const std::string &message, const std::string &parameters);
	void							toUpper(std::string &command);
	std::string						toUpper(const std::string &command);
	std::string						getParameterStr(std::string::const_iterator iterator, const std::string &message);
public:
									Msg(void);
									Msg(const std::string &message);
									Msg(const std::string &prefix, const std::string &command, const std::string &parameters);
									~Msg(void);
	Msg							&operator=(const Msg &message);
	const std::string				getPrefix(void) const;
	const std::string				getCommand(void) const;
	const std::string				getParameter(const int &index) const;
	std::vector<std::string>		getParameters(void) const;
	const std::string				&getTotalMsg(void) const;
};

#endif
