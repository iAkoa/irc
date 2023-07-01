
#include "../header/Server.hpp"

void	Server::part(const Message &message)
{
	std::string	channel;
	std::string	reason;
	std::string	user;
	int fd = message.getUser().getFd();

	user = message.getUser().getNickname();
	channel = getWord(message.getParameters(), 0);
	reason = getEndFrom(message.getParameters(), 1);

	std::cout << "channel :" << channel << "." << std::endl;
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
	it->second.getUsers().erase(user);
	it->second.getAdmins().erase(user);
	std::cout << "user " << user << " successfully leaved from channel " << channel << ", reason : " << reason << "." << std::endl;
}