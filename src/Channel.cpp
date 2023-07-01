#include "../header/Channel.hpp"
// canonical
Channel::Channel() :
_invite_only(false),
_restricted(false),
_user_limit(1000),
_iskey(false)
{
}

Channel::Channel(std::string name) : _name(name),
_invite_only(false),
_restricted(false),
_user_limit(1000),
_iskey(false)
{
	return ;
}

Channel::Channel(std::string name, std::string key) : _name(name), _key(key),
_invite_only(false),
_restricted(false),
_user_limit(1000),
_iskey(true)
{
	return ;
}

Channel::Channel(std::string name, std::string key, User *admin) : _name(name), _key(key),
_invite_only(false),
_restricted(false),
_user_limit(1000),
_iskey(true)
{
	_admins.insert(std::make_pair(admin->getNickname(), admin));
	return ;
}

Channel::Channel(std::string name, User *admin) : _name(name),
_invite_only(false),
_restricted(false),
_user_limit(1000),
_iskey(false)
{
	_admins.insert(std::make_pair(admin->getNickname(), admin));
	return ;
}

Channel::~Channel(void)
{
	return ;
}

Channel::Channel(Channel const &src)
{
	*this = src;
	return ;
}

Channel &	Channel::operator=(Channel const &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_key = rhs.getKey();
		this->_admins = rhs.getAdmins2();
		this->_users = rhs.getUsers2();
		this->_invited = rhs.getInvited2();
		this->_iskey= rhs.getIsKey();
		this->_user_limit = rhs.getUserLimit();
		/*
		*/
	}
	return (*this);
}

// getters 

std::string	Channel::getName(void) const
{
	return (this->_name);
}

std::string	Channel::getKey(void) const
{
	return (this->_key);
}

bool	Channel::getIsKey(void) const
{
	return (this->_iskey);
}

std::string		Channel::getTopic(void) const
{
	return (this->_topic);
}

bool	Channel::getInviteOnly(void) const
{
	return (this->_invite_only);
}

bool	Channel::getRestricted(void) const
{
	return (this->_restricted);
}

int		Channel::getUserLimit(void) const
{
	return (this->_user_limit);
}

std::map<std::string, User *>	&Channel::getUsers(void) 
{
	return (this->_users);
}

std::map<std::string, User *>	&Channel::getAdmins(void) 
{
	return (this->_admins);
}

std::map<std::string, User *>	&Channel::getInvited(void) 
{
	return (this->_invited);
}

std::map<std::string, User *>	Channel::getUsers2(void) const
{
	return (this->_users);
}

std::map<std::string, User *>	Channel::getAdmins2(void) const
{
	return (this->_admins);
}

std::map<std::string, User *>	Channel::getInvited2(void) const
{
	return (this->_invited);
}

// setters 

void	Channel::setName(std::string name)
{
	this->_name = name;
}

void	Channel::setIsKey(bool iskey)
{
	this->_iskey = iskey;
}

void	Channel::setKey(std::string key)
{
	this->_key = key;
}

void	Channel::setTopic(std::string topic)
{
	this->_topic= topic;
}

void	Channel::setInviteOnly(bool invite_only)
{
	this->_invite_only = invite_only;
}

void	Channel::setRestricted(bool restricted)
{
	this->_restricted = restricted;
}

void	Channel::setUserLimit(int user_limit)
{
	this->_user_limit= user_limit;
}

/*
Channel( Channel const &src)
{

}

Channel &	operator=( Channel const &rhs);

		std::string		getName( void ) const;
		std::string		getKey( void ) const;
		std::string		getTopic( void ) const;
		bool			getInviteOnly( void ) const;

		std::list<User>	getUser( void ) const;
		std::list<User>	getAdmin( void ) const;

		void			setName( std::string name );
		void			setKey( std::string key );
		void			setTopic( std::string topic );
		void			setInviteOnly( bool invite_only );
*/

