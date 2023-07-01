#include "../header/Server.hpp"


std::vector<std::string> Server::splitString(const std::string& str, const std::string& separator) 
{
	std::vector<std::string> users;
	std::istringstream iss(str);
	std::string user;

	while (std::getline(iss, user, separator[0]))
	{
		users.push_back(user);
		if (separator[0] == ':')
		{
			std::getline(iss, user, '\n');
			users.push_back(user);
			return users;
		}
	}
	return users;
}

void	Server::privmsg(const Message &message)
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
		std::cout << users_msg.size() << std::endl;
		found = users_msg[0].find(',');
		if (found != std::string::npos)
			users = splitString(users_msg[0], ",");
		else
			users = splitString(users_msg[0], " ");
		if (!users.size())
		{
			std::cout << "NO User\n";
			return ;
		}
	}
	else
		std::cout << "NO Message\n";
	for (const std::string& user : users) 
	{
		std::cout << user << std::endl;
		if(_users.exist(user))
		{
			write(_users[user].getFd(), &users_msg[1], users_msg[1].size());
			write(_users[user].getFd(), "\r\n", 2);
		}
		else
			std::cout << user << "don't exist" << std::endl;
	}
}