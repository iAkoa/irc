#include "../header/Server.hpp"

void	Server::notice(const Message &message)
{
	std::vector<std::string> users_msg;
	std::vector<std::string> users;
	std::size_t found = message.getParameters().find(':');
	std::cout << "-------------------------\n";
	std::cout << "[user message] --> "<< message.getParameters() << std::endl;
	if (found != std::string::npos)
	{
		users_msg = splitString(message.getParameters(), ":");
		std::cout << "-------------------------\n";
		std::cout << "[user user user] --> " << users_msg[0] << std::endl;
		found = users_msg[0].find(',');
		if (found != std::string::npos)
			users = splitString(users_msg[0], ",");
		else
			users = splitString(users_msg[0], " ");
	}
	else
		std::cout << "NO Message\n";
}