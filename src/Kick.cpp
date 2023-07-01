
#include "../header/Server.hpp"

void	Server::kick(const Message &message)
{
	std::string	channel;
	std::string	user;
	std::string	reason;
	int fd = message.getUser().getFd();

	channel = getWord(message.getParameters(), 0);
	user = getWord(message.getParameters(), 1);
	reason = getEndFrom(message.getParameters(), 2);

	std::cout << "channel :" << channel << "." << std::endl;
	std::cout << "user:" << user << "." << std::endl;
	std::cout << "reason:" << reason << "." << std::endl;

	if (reason.empty()) // reason is empty 
		reason = "with no reason specified."; // default message
	std::map<std::string, Channel>::iterator it;
	it = _channels.find(channel);
	if (it == _channels.end()) // channel doesn't exist
	{
		respond(message.getUser().getNickname(), ERR_NOSUCHCHANNEL, fd);
		std::cout << "error. no such channel." << std::endl;
		return ;
	}
	if (it->second.getAdmins().find(message.getUser().getNickname()) == it->second.getAdmins().end()) // protected mode && user dont have the rights 
	{
		std::cout << "error. operator privilege needed." << std::endl;
		respond(message.getUser().getNickname(), ERR_CHANOPRIVSNEEDED, fd);
		return ;
	}
	it->second.getUsers().erase(user);
	std::cout << "user " << user << " successfully kicked from channel " << channel << ", reason : " << reason << "." << std::endl;
}