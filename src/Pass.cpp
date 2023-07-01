
#include "../header/Server.hpp"
using namespace std;

void Server::pass(const Message &message)
{
	string answer;
	string param = message.getParameters();
	string password = word(param, 0, true);
	if (password != _password)
		answer = string(ERR_PASSWDMISMATCH) + " :Password incorrect"; 
	else if (password == "")
		answer = string(ERR_NEEDMOREPARAMS) + " " + message.getCommand() + " :Not enough parameters";
	else
	{
		message.getUser().setLevel(1);
		checkAuth(message.getUser());
	}
	respond(message.getUser().getNickname(), answer, message.getFd());
}