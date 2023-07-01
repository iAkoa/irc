#include "../header/Server.hpp"
using namespace std;

void Server::nick(const Message &message)
{
	string answer;
	string param = message.getParameters();
	string nickname = word(param, 0, false);

		cout << "Here 1" << endl;
	if ((message.getUser().getLevel() & 1) == 0)
		answer = string(ERR_PASSWDMISMATCH) + " :Password incorrect"; 
	else if (message.getParameters() == "")
	 	answer = ERR_NONICKNAMEGIVEN;
	else if (_users.exist(nickname))
	{
		answer = ERR_ERRONEUSNICKNAME;
		cout << "Here 2" << endl;
	}
	else if (false) // mettre une condition valable
		answer = ERR_ERRONEUSNICKNAME;
	else
	{
		_users.addKey(message.getFd(), nickname);
		message.getUser().setNickname(nickname);
		message.getUser().setLevel(4);
		checkAuth(message.getUser());
	}
	respond(nickname, answer, message.getFd());
	return ;
}