
#include "../header/Server.hpp"

std::string	Server::inviteGetNickname(std::string parameters)
{
	std::string	nickname;
	int	i = 0;
	int	j = 0;

	while (parameters[i] && parameters[i] != ' ')
	{
		if (!parameters[i + 1]|| parameters[i + 1] == ' ')
		{
			nickname = parameters.substr(i - j, j + 1);
		}
		i++;
		j++;
	}
	return (nickname);
}

std::string	Server::inviteGetChannel(std::string parameters)
{
	std::string	channel;
	size_t i = parameters.find(' ');
	size_t j = 0;

	while (parameters[i])
	{
		if (!parameters[i + 1])
		{
			channel = parameters.substr(i - j, j + 1);
		}
		i++;
		j++;
	}
	return (channel);
}

void	Server::invite(const Message &message)
{
	std::string nickname;
	std::string	channel;
	int fd = message.getUser().getFd();

	nickname = inviteGetNickname(message.getParameters());
	channel = inviteGetChannel(message.getParameters());

	std::map<std::string, Channel>::iterator it;
	it = _channels.find(channel);

	if (it == _channels.end()) // channel doesn't exist
	{
		// ERR_NOSUCHCHANNEL (403) 
		std::cout << "error. no such channel." << std::endl;
		return ;
	}

	if (it->second.getUsers().find(message.getUser().getNickname()) == it->second.getUsers().end()) // user not in channel
	{
		// DOESNT WORK I DONT KNOW WHY. WILL COME BACK TO IT LATER I THINK
		std::cout << "error. user not in channel." << std::endl;
		// ERR_NOTONCHANNEL (442)
		return ;
	}	
	if (it->second.getInviteOnly() && it->second.getAdmins().find(message.getUser().getNickname()) == it->second.getAdmins().end()) // invite only and user != admin
	{
		std::cout << "error. operator privilege needed." << std::endl;
		// ERR_CHANOPRIVNEEDED (482)
		return ;
	}
	if (it->second.getUsers().find(nickname) != it->second.getUsers().end()) // target user is already in channel
	{
		// DOESNT WORK I DONT KNOW WHY. WILL COME BACK TO IT LATER I THINK
		std::cout << "error. user is already in channel." << std::endl;
		// ERR_USERONCHANNEL
		return ;
	}	
	std::cout << "user " << message.getUser().getNickname() << " has been invited to the channel " << channel << "." << std::endl;
	it->second.getInvited().insert(std::make_pair(nickname, &message.getUser()));
	// add user to invited list
	// RPL INVITELIST(336) ? ending with a RPL_ENDOFINVITELIST(337)
	return ;
}