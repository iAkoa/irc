#include "../header/Message.hpp"
// canonical form
/*
Message::Message(std::string message) : _message(message)
{
	return ;
}
*/
Message::Message(std::string message, User *user) : _message(message), _user(user)
{
	return ;
}

Message::Message(std::string message, User &user) : _message(message)
{
	(void) user;
	return ;
}

Message::~Message(void)
{
	return ;
}

Message::Message(Message const &src)
{
	*this = src;
	return ;
}

Message &	Message::operator=(Message const &rhs)
{
	if (this != &rhs)
		this->_message = rhs.getMessage();
	return (*this);
}

// getters 

std::string	Message::getMessage(void) const
{
	return (this->_message);
}

std::string	Message::getPrefix(void) const
{
	return (this->_prefix);
}

std::string		Message::getCommand(void) const
{
	return (this->_command);
}

std::string Message::getParameters(void) const
{
	return (this->_parameters);
}

User	&Message::getUser(void) const
{
	return (*this->_user);
}

int Message::getFd( void ) const
{
	return (_user->getFd());
}

std::string		Message::getTags(void) const
{
	return (this->_tags);
}

// setters 

void	Message::setMessage(std::string message)
{
	this->_message = message;
}

void	Message::setPrefix(std::string prefix)
{
	this->_prefix = prefix;
}

void	Message::setCommand(std::string command)
{
	this->_command = command;
}

void	Message::setParameters(std::string parameters)
{
	this->_parameters = parameters;
}

void	Message::setUser(User *user)
{
	this->_user = user;
}

void	Message::setTags(std::string tags)
{
	this->_tags = tags;
}

void	Message::parseTag(std::string src, size_t start)
{
	std::cout << "parseTag called." << std::endl;
	size_t	pos = 0;

	if (src[0] == '@')
	{
		pos = src.find(' ');
		if (pos != std::string::npos)
			_tags = src.substr(start, pos - start);
		else 
		{
			std::cout << "parsing error." << std::endl;
			return ;
		}
	}
	while (src[pos] == ' ')
		pos++;
	std::cout << "pos = " << pos << std::endl;
	parsePrefix(src, pos);
	
}

void	Message::parsePrefix(std::string src, size_t start)
{
	std::cout << "parsePrefix called." << std::endl;
	size_t	pos = 0;

	std::cout << "src[start] = " << src[start] << std::endl;
	while (src[start] == ' ')
		start++;
	if (src[start] == ':')
	{
		std::cout << "prefix detected" << std::endl;
		pos = src.find(' ', start);
		if (pos != std::string::npos)
			_prefix = src.substr(start, pos - start);
		else
			std::cout << "parsing error." << std::endl;

	}
	std::cout << "pos = " << pos << std::endl;
	parseCommand(src, pos + 1);
}

void	Message::parseCommand(std::string src, size_t start)
{
	// std::cout << "parseCommand called." << std::endl;
	size_t	pos = 0;

	while (src[start] == ' ')
		start++;
	pos = src.find(' ', start);
	if (pos != std::string::npos)
	{
		_command = src.substr(start, pos - start);	
		while (src[pos] == ' ')
			pos++;
		_parameters = src.substr(pos);
	}
	else
		_command = src.substr(start);
}

void	Message::parseMessage(void)
{
	std::string src = _message;

	if (_message.size() <= 0)
		return ;
	if (_message[0] == '@')
		parseTag(src, 0);
	else if (_message[0] == ':')
		parsePrefix(src, 0);
	else
		parseCommand(src, 0);
}


std::ostream &	operator << ( std::ostream & o, Message const & i )
{
	o << "message :" << i.getMessage() << std::endl;
	o << "prefix :" << i.getPrefix() << std::endl;
	o << "tags :" << i.getTags() << std::endl;
	o << "command :" << i.getCommand() << std::endl;
	o << "parameters :" << i.getParameters() << std::endl;

	return (o);
}