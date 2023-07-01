#include "../header/Server.hpp"

std::list<std::string>	Server::joinGetChannels(std::string parameters)
{
	std::list<std::string>	channels;
	int	i = 0;
	int	j = 0;

	while (parameters[i] && parameters[i] != ' ')
	{
		if (parameters[i] == ',')
		{
			channels.push_back(parameters.substr(i - j, j));
			j = 0;
			i++;
		}
		else if (!parameters[i + 1]|| parameters[i + 1] == ' ')
		{
			channels.push_back(parameters.substr(i - j, j + 1));
		}
		j++;
		i++;
	}
	return (channels);
}

std::list<std::string>	Server::joinGetKeys(std::string parameters)
{
	std::list<std::string>	keys;
	int	j = 0;
	std::size_t	i = parameters.find(' ');

	if (i == std::string::npos)
		return (keys);
	i++;
	while (parameters[i])
	{
		if (parameters[i] == ',')
		{
			keys.push_back(parameters.substr(i - j, j));
			j = 0;
			i++;
		}
		else if (!parameters[i + 1])
		{
			keys.push_back(parameters.substr(i - j, j + 1));
		}
		j++;
		i++;
	}
	return (keys);
}


void	Server::join(const Message &message)
{
	std::list<std::string>	channels;
	std::list<std::string>	keys;
	std::map<std::string, std::string>	map;
	int fd = message.getUser().getFd();
	std::string answer;
/*
	if () // special argument "0"
	{
		// call PART
		return ;
	}
	if () // user don't have enough rights for this command
		return ;
*/
	// parse parameters to get channel and key
	// joinParseWrongFormat();
/*
*/
	channels = joinGetChannels(message.getParameters()); // get all channels
	for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (!beginWith(*it, '#'))
		{
			std::cout << "error. channels must begin with # " << *it << std::endl;
		}
		std::cout << "channels : " << *it << std::endl;
	}

	keys = joinGetKeys(message.getParameters()); // get all keys
	for (std::list<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
	{
		std::cout << "keys: " << *it << std::endl;
	}
	if (channels.size() < keys.size())
	{
		std::cout << "parsing error. too many keys." << std::endl;
		respond(message.getUser().getNickname(), ERR_NEEDMOREPARAMS, fd);
		// ERR_NEEDMOREPARAMS ?
		return ;
	}

	std::list<std::string>::iterator keyIter = keys.begin();
	for (std::list<std::string>::iterator it = channels.begin(); it != channels.end(); ++it )
	{
		std::string	channel = *it;
		std::string key;
		if (keyIter != keys.end())
			key = *keyIter;
		std::map<std::string, Channel>::iterator	mapIter;
		mapIter = _channels.find(channel);

		std::cout << "key = " << key << std::endl;
		std::cout << "channel = " << channel << std::endl;
		std::cout << "petit test en legende 1" << std::endl;
		if (!beginWith(channel, '#'))
		{
			std::cout << "error. channels must begin with # " << *it << std::endl;
			return ;
		}
		if (mapIter == _channels.end())	
		{
			std::cout << "new channel" << std::endl;
			if (keyIter != keys.end())
			{
				//_channels[channel] = Channel(channel);
				//_channels.insert(std::make_pair(channel, Channel(channel, key, &message.getUser())));
				_channels[channel] = Channel(channel, key, &message.getUser());
	
				std::cout << "user " << message.getUser().getNickname() << " has created the channel " << *it << " with password " << key << "." << std::endl;
				respondC(message.getUser().getNickname(), std::string("JOIN ") + channel, _channels[channel]);
				//_channels[channel] = Channel(channel, key);
			}
			else
			{
				_channels[channel] = Channel(channel, &message.getUser());
				//_channels.insert(std::make_pair(channel, Channel(channel, &message.getUser())));
				std::cout << "user " << message.getUser().getNickname() << " has created the channel " << *it << "." << std::endl;
				respondC(message.getUser().getNickname(), std::string("JOIN ") + channel, _channels[channel]);
			}
		}
		else
		{
			std::cout << "channel already exists" << std::endl;
			if (mapIter->second.getInviteOnly() == true)
			{
				std::cout << "channel has invite only set on." << std::endl;
				if (mapIter->second.getInvited().find(message.getUser().getNickname()) == mapIter->second.getInvited().end())
				{
					std::cout << "user not invited to invite only channel." << std::endl;
					respond(message.getUser().getNickname(), ERR_INVITEONLYCHAN, fd);
					return ;
				}
			}
			//else 
			if (mapIter->second.getIsKey() == true)
			{
				std::cout << "password required to access this channel" << std::endl;
				if (keyIter == keys.end() || mapIter->second.getKey() != key)
				{
					std::cout << "good key :" << mapIter->second.getKey() << "." << std::endl;
					std::cout << "your key :" << key << "." << std::endl;
					std::cout << "wrong password" << std::endl;
					respond(message.getUser().getNickname(), ERR_BADCHANNELKEY, fd);
					return ;
				}
			}
			if (mapIter->second.getUsers().find(message.getUser().getNickname()) != mapIter->second.getUsers().end()
			|| mapIter->second.getAdmins().find(message.getUser().getNickname()) != mapIter->second.getAdmins().end())
			{
				std::cout << "message user name :" << message.getUser().getNickname() << std::endl;
				std::cout << "user already in channel" << std::endl;
				respond(message.getUser().getNickname(), ERR_USERONCHANNEL, fd);
				return ;
			}
			std::cout << "petit test en legende 9" << std::endl;
			if (mapIter->second.getUsers().size() + mapIter->second.getAdmins().size() + 1 > static_cast<unsigned long>(mapIter->second.getUserLimit()))
			{
				std::cout << "user limit reached. cannot join channel." << std::endl;
				respond(message.getUser().getNickname(), ERR_CHANNELISFULL, fd);
				return ;
			}
			mapIter->second.getUsers()[message.getUser().getNickname()] = &message.getUser();
			if(!mapIter->second.getTopic().empty()) // topic
			{
				std::cout << "Topic :" << mapIter->second.getTopic() << std::endl;
			}
			std::cout << "user " << message.getUser().getNickname() << " has joined the channel " << *it << "." << std::endl;
			respondC(message.getUser().getNickname(), std::string("JOIN ") + channel, _channels[channel]);
				// send message ("<user> has joined the channel <channel>")
			// sens the list of users joined to the channel(with RPL_NAMREPLY(353)s + one RPL_ENDOFNAMES(366))
		}
		keyIter++;
	}
}