/* UNFINISHED */
// constructors
#include "../header/User.hpp"

User::User(std::string name) : _level(0), _username(name)
{
	(void) _level;
	return ;
}

User::User(int fd) : _fd(fd), _level(0)
{
	return ;
}

User::User(void)
{
	return ;
}

User::~User(void)
{
	return ;
}

User::User(User const & src)
{
	*this = src;
	return ;
}

User &	User::operator=(User const &rhs)
{
	_fd = rhs._fd;
	_level = rhs._level;
	_username = rhs._username;
	_nickname = rhs._nickname;
	_password = rhs._password;
	_operator = rhs._operator;
	_ip = rhs._ip;
	return (*this);
}

// getters 

std::string	User::getUsername(void) const
{
	return (this->_username);
}

std::string	User::getNickname(void) const
{
	return (this->_nickname);
}

std::string	User::getPassword(void) const
{
	return (this->_password);
}

std::string		User::getIP(void) const
{
	return (this->_ip);
}

bool	User::isOperator(void) const
{
	return (this->_operator);
}

int		User::getFd(void) const
{
	return (this->_fd);
}

int		User::getLevel(void) const
{
	return (this->_level);
}

// setters 

void	User::setUsername(std::string username)
{
	this->_username = username;
}

void	User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void	User::setPassword(std::string password)
{
	this->_password = password;
}

void	User::setIP(std::string ip)
{
	this->_ip = ip;
}

void	User::setOperator(bool op)
{
	this->_operator = op;
}

void	User::setFd(int fd)
{
	this->_fd = fd;
}

void	User::setLevel(int level)
{
	this->_level |= level;
}