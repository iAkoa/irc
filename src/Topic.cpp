
#include "../header/Server.hpp"

std::string	Server::topicGetTopic(std::string parameters)
{
	std::string	topic;
	size_t i = parameters.find(' ');
	size_t j = 0;

	while (parameters[i])
	{
		if (!parameters[i + 1])
		{
			topic = parameters.substr(i - j, j + 1);
		}
		i++;
		j++;
	}
	return (topic);
}

std::string	Server::topicGetChannel(std::string parameters)
{
	std::string	channel;
	int	i = 0;
	int	j = 0;

	while (parameters[i] && parameters[i] != ' ')
	{
		if (!parameters[i + 1]|| parameters[i + 1] == ' ')
		{
			channel = parameters.substr(i - j, j + 1);
		}
		i++;
		j++;
	}
	return (channel);
}

void	Server::topic(const Message &message)
{
	std::string	channel;
	std::string	topic;
	int fd = message.getUser().getFd();

	channel = topicGetChannel(message.getParameters());
	topic = topicGetTopic(message.getParameters());

	std::cout << "channel :" << channel << "." << std::endl;
	std::cout << "topic :" << topic << "." << std::endl;

	std::map<std::string, Channel>::iterator it;
	it = _channels.find(channel);
	if (it == _channels.end()) // channel doesn't exist
	{
		// ERR_NOSUCHCHANNEL (403) 
		respond(message.getUser().getNickname(), ERR_NOSUCHCHANNEL, fd);
		std::cout << "error. no such channel." << std::endl;
		return ;
	} //else if (it->second.getUsers().find(message.getUser().getNickname()) == it->second.getUsers().end()) // channel exists and user is not part of the channel

	std::cout << "message user getnickname :" << message.getUser().getNickname() << "." << std::endl;
	//std::cout << "it second user find:" << it->second.getUsers().find(message.getUser().getNickname())->second->getNickname() << "." << std::endl;
	if (it->second.getUsers().find(message.getUser().getNickname()) == it->second.getUsers().end())
	{
		// DOESNT WORK I DONT KNOW WHY. WILL COME BACK TO IT LATER I THINK
		std::cout << "error. user not in channel." << std::endl;
		respond(message.getUser().getNickname(), ERR_NOTONCHANNEL, fd);
		// ERR_NOTONCHANNEL (442)
		return ;
	}	
	else // channel exists and user is in it
	{
		if (it->second.getRestricted() && it->second.getAdmins().find(message.getUser().getNickname()) == it->second.getAdmins().end()) // protected mode && user dont have the rights 
		{
			std::cout << "error. operator privilege needed." << std::endl;
			respond(message.getUser().getNickname(), ERR_CHANOPRIVSNEEDED, fd);
			// ERR_CHANOPRIVNEEDED (482)
			return ;
		}
		else 
		{
			it->second.setTopic(topic);
			std::cout << "new topic " << topic << " successfully set on channel" << it->second.getName() << "." << std::endl;
			// change topic, send every chan member the new topic or cleared
		}
	}
}