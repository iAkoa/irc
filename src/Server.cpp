#include "Server.hpp"
#include "NumericReplies.hpp"

using namespace std;
// canonical
Server::Server(void)
{
	init();
	return ;
}

Server::Server(int port, const std::string password) : 
_sockets(port),
_password(password)
{
	init();
	return ;
}

Server::~Server(void)
{
	return ;
}

Server::Server(Server const &src)
{
	*this = src;
}

Server &	Server::operator=(Server const & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

// getters

DMap<int, std::string, User>	Server::getUsers(void) const
{
	return (this->_users);
}

std::map<std::string, Channel>	Server::getChannels(void) const
{
	return (this->_channels);
}

void Server::init()
{
	_commands["NICK"] = &Server::nick;
	_commands["PASS"] = &Server::pass;
	_commands["USER"] = &Server::user;

	_commands["KICK"] = &Server::kick;
	_commands["MODE"] = &Server::mode;
	_commands["PART"] = &Server::part;
	_commands["JOIN"] = &Server::join;
	_commands["TOPIC"] = &Server::topic;

	_commands["PRIVMSG"] = &Server::privmsg;
	_commands["NOTICE"] = &Server::notice;
}

void Server::start()
{
	std::cout << "on va la ?" << std::endl;
	while (1)
    {
        _sockets.update();
        std::vector<Response> resp = _sockets.getMsg();
        for (vector<Response>::iterator it = resp.begin(); it != resp.end(); it++)
        {
            cout << "Message | " << it->msg << endl;
			if (_users.find(it->fd) == _users.end())
				_users[it->fd] = User(it->fd);

            Message message(it->msg, &_users[it->fd]);
            message.parseMessage();
			chooseCommand(message);  
			/*
			if (isValidString(message.getParameters()) && isValidString(message.getCommand()))
				chooseCommand(message);  
			else
				std::cout << "please input only alphanumerical characters, and appropriate separators (,#&_)" << std::endl;
				*/
        }
    }
}

string	Server::word(const string &s, int n, bool all)
{
	int i = 0;
	int j;

	while (s[i] && s[i] == ' ')
		i++;	
	for (; n > 0; n--)
	{
		while (s[i] && s[i] != ' ')
			i++;	
		while (s[i] && s[i] == ' ')
			i++;		
	}
	j = i;
	while (s[j] && (s[j] != ' ' || all))
		j++;	
	return (s.substr(i, j));
}

void Server::respond(string source, string answer, const int fd)
{
	if (answer != "")
	{
		answer = ":" + source + " " + answer + "\r\n";
		write(fd, answer.c_str(), answer.size());
		cout << "Answer | " << answer << endl;
	}
}

void Server::respondC(string source, string answer, Channel channel)
{
	map<string, User *> &users = channel.getUsers();
	map<string, User *> &admins = channel.getAdmins();
	for (map<string, User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		respond(source, answer, it->second->getFd());
		cout << "test" << endl;
	}
	for (map<string, User *>::iterator it = admins.begin(); it != admins.end(); it++)
	{
		cout << "test" << endl;
		respond(source, answer, it->second->getFd());
	}
	cout << "test2" << endl;
}

void Server::checkAuth(User &user)
{
	if(user.getLevel() != (1 | 2 | 4))
		return;
	user.setLevel(8);
	respond(user.getNickname(), string(RPL_WELCOME) + " " + user.getNickname() + " :Welcome to the Abyssal Network, " + user.getNickname(), user.getFd());
	respond(user.getNickname(), string(RPL_YOURHOST) + " " + user.getNickname() + " :Your host is AbyssalServer, running version 1.0", user.getFd());
	respond(user.getNickname(), string(RPL_CREATED) + " " + user.getNickname() + " :This server was created the 14-06-2023", user.getFd());
	respond(user.getNickname(), string(RPL_MYINFO) + " " + user.getNickname() + " AbyssalServer 1.0 i itokl", user.getFd());
	respond(user.getNickname(), string(RPL_ISUPPORT) + " " + user.getNickname() + " <1-13 tokens> :are supported by this server", user.getFd());
}

void Server::chooseCommand(const Message &message)
{
	if (_commands.find(message.getCommand()) == _commands.end())
		{
			std::cerr << "No matching command." << std::endl;
			return ;
		}
	(this->*(_commands[message.getCommand()]))(message);
	return ;
}

std::string	Server::getWord(std::string src, int word)
{
	std::string ret;
	std::size_t i;
	std::size_t j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (n < word)
	{
		j = i;
		i = src.find(' ', j);
		while (src[i] && src[i] == ' ')
			i++;
		n++;
	}
	j = 0;
	while (src[i] && src[i] != ' ')
	{
		if (!src[i + 1] || src[i + 1] == ' ')
			ret = src.substr(i - j, j + 1);
		i++;
		j++;
	}
	return (ret);
}

std::string	Server::getEndFrom(std::string src, int word)
{
	std::string ret;
	std::size_t i;
	std::size_t j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (n < word)
	{
		i = src.find(' ', j);
		while (src[i] && src[i] == ' ')
			i++;
		j = i + 1;
		n++;
	}
	j = 0;
	while (src[i])
	{
		if (!src[i + 1])
			ret = src.substr(i - j, j + 1);
		i++;
		j++;
	}
	return (ret);
}

int	Server::countWords(std::string src)
{
	std::string ret;
	std::size_t i;
	std::size_t j;
	int n;

	i = 0;
	n = 0;
	while (src[i])
	{
		if (src[i] != ' ')
			n++;
		i = src.find(' ', j);
		while (src[i] && src[i] == ' ')
			i++;
		j = i + 1;
	}
	return (n);
}

bool	Server::beginWith(std::string src, char c)
{
	if (src.empty())
		return (false);
	else if (src[0] != c)
		return (false);
	return (true);
}
// specific functions
bool	Server::isStrAlNum(std::string src)
{
	char c;

	for (size_t i = 0; i < src.length(); ++i) {
		c = src[i];
		if( !std::isalnum(src[i])
			&& src[i] != '_')
			return (false);
	}
	return (true);
}

bool	Server::isValidString(std::string src)
{
	char c;

	if (src.length() >= 100)
		return (false);
	for (size_t i = 0; i < src.length(); ++i) {
		c = src[i];
		if( !std::isalnum(c)
			&& c != '_'
			&& c != '#'
			&& c != ','
			&& c != '+'
			&& c != ':'
			&& c != '-'
			&& c != '&'
			&& c != ' ')
			return (false);
	}
	return (true);
}
