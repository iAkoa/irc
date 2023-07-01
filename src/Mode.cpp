
#include "../header/Server.hpp"

bool	Server::isInCharset(std::string charset, char c)
{
	std::size_t i;

	i = charset.find(c);
	if (i != std::string::npos)
		return true;
	else
		return false;
}

bool	Server::isUnique(std::string modestring, char c)
{
	int count = 0;
	for (int i = 0; modestring[i] && modestring[i] != ' '; i++)
	{
		if (modestring[i] == c)
			count++;
	}
	if (count != 1)
		return (false);
	return (true);
}

int	Server::isParsingModeOk(std::string modestring, std::map<std::string, Channel>::iterator it)
{
	int count = 0;
	int add = 0;

	if (modestring[0] != '+' && modestring[0] != '-')
	{
		std::cout << "mode : parsing error. modesting needs to begin with + or -" << std::endl;
		return (-1);
	}
	for (int i = 0; modestring[i] && modestring[i] != ' '; i++)
	{
		if (!isInCharset("+-tloik", modestring[i]))
		{
			std::cout << "mode : parsing error. available modes : tloik" << std::endl;
			return (-1);
		}
		if (!isUnique(modestring, modestring[i]))
		{
			std::cout << "mode : parsing error. double input" << std::endl;
			return (-1);
		}
		if ((modestring[i] == '+' || modestring[i] == '-') && (!modestring[i + 1] || modestring[i + 1] == ' '))
		{
			std::cout << "mode : parsing error. empty + or -" << std::endl;
			return (-1);
		}
	}
	for (int i = 0; modestring[i] && modestring[i] != ' '; i++)
	{
		if (modestring[i] == '+')
			add = 1;
		else if (modestring[i] == '-')
			add = -1;
		else if (add == 1 && modestring[i] == 'l')
		{
			count++;
			if (!isdigit(getWord(modestring, count)[0]))
			{
				std::cout << "mode : parsing error. +l failed.";
				return (-1);
			}
		}
		else if (add == 1 && modestring[i] == 'k')
		{
			count++;
		}
		else if (modestring[i] == 'o')
		{
			count ++;
			std::string user = getWord(modestring, count);
			if (user.empty())
			{
				std::cout << "mode : parsing error. no such user.";
				return (-1);
			}
			if (it->second.getUsers().find(user) == it->second.getUsers().end()) // user not in channel
			{
				std::cout << "mode : user not in channel." << std::endl;
				return (-1);
			}
		}
	}
	std::cout << "count = " << count << std::endl;
	std::cout << "countwords = " << countWords(modestring) << std::endl;
	if (count + 1 != countWords(modestring))
	{
		std::cout << "Error. mode : need more parameters." << std::endl;
		return (-1);
	}
	return (0);
}

void	Server::mode(const Message &message)
{
	std::string	channel;
	std::string	modestring;
	int fd = message.getUser().getFd();

	channel = getWord(message.getParameters(), 0);
	modestring = getEndFrom(message.getParameters(), 1);

	std::cout << "channel = " << channel << std::endl;
	std::cout << "modestring = " << modestring << std::endl;

	// get target 
	// get modestring

	std::map<std::string, Channel>::iterator it;
	it = _channels.find(channel);
	if (it == _channels.end()) // channel doesn't exist
	{
		respond(message.getUser().getNickname(), ERR_NOSUCHCHANNEL,fd);
		std::cout << "error. no such channel." << std::endl;
		return ;
	}
	if (modestring.empty()) // no modestring 
	{
		std::cout << "error. empty modestring" << std::endl;
		respond(message.getUser().getNickname(), RPL_CHANNELMODEIS, fd);
	}
	if (it == _channels.end()) // channel doesn't exist
	{
		respond(message.getUser().getNickname(), ERR_NOSUCHCHANNEL, fd);
		std::cout << "error. no such channel." << std::endl;
		return ;
	}
	if (it->second.getAdmins().find(message.getUser().getNickname()) == it->second.getAdmins().end()) // user dont have the rights 
	{
		std::cout << "error. operator privilege needed." << std::endl;
		respond(message.getUser().getNickname(), ERR_CHANOPRIVSNEEDED, fd);
		return ;
	}

	// parse command
	if (isParsingModeOk(modestring, it) == -1)
	{
		std::cout << "mode fail" << std::endl;
		return ;
	}
	int add = 0;
	int count = 0;
	for (int i = 0; modestring[i] && modestring[i] != ' '; i++)
	{
		if (modestring[i] == '+')
			add = 1;
		else if (modestring[i] == '-')
			add = -1;
		// o
		else if (add == 1 && modestring[i] == 'o')
		{
			count++;
			std::string user = getWord(modestring, count);
			it->second.getAdmins()[user] = it->second.getUsers()[user];
			// remove guy from users ?
			std::cout << "mode +o successfully set" << std::endl;
		}
		else if (add == -1 && modestring[i] == 'o')
		{
			std::string user = getWord(modestring, count);
			it->second.getAdmins().erase(user);
			// add guy to users ?
			std::cout << "mode +o successfully unset" << std::endl;
		}
		// l
		else if (add == 1 && modestring[i] == 'l')
		{
			count++;
			int nb = atoi(getWord(modestring, count).c_str());
			if (nb == 0)
				std::cout << "invalid limit input." << std::endl;
			it->second.setUserLimit(atoi(getWord(modestring, count).c_str()));
			// will need more security
			std::cout << "mode +l successfully set" << std::endl;
		}
		else if (add == -1 && modestring[i] == 'l')
		{
			it->second.setUserLimit(1000);
			std::cout << "mode +l successfully unset" << std::endl;
		}
		// k
		else if (add == 1 && modestring[i] == 'k')
		{
			count++;
			it->second.setIsKey(true);
			it->second.setKey(getWord(modestring, count));
			std::cout << "mode +k successfully set" << std::endl;
		}
		else if (add == -1 && modestring[i] == 'k')
		{
			it->second.setIsKey(false);
			it->second.setKey("");
			std::cout << "mode +k successfully unset" << std::endl;
		}
		// t
		else if (add == 1 && modestring[i] == 't')
		{

			it->second.setRestricted(true);
			std::cout << "mode +t successfully set" << std::endl;
		}
		else if (add == -1 && modestring[i] == 't')
		{

			it->second.setRestricted(false);
			std::cout << "mode +t successfully unset" << std::endl;
		}

		// i
		else if (add == 1 && modestring[i] == 'i')
		{
			it->second.setInviteOnly(true);
			std::cout << "mode +i successfully set" << std::endl;
		}
		else if (add == -1 && modestring[i] == 'i')
		{
			it->second.setInviteOnly(false);
			std::cout << "mode +i successfully unset" << std::endl;
		}
	}
	std::cout << "mode success" << std::endl;
	return ;
}