/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:34:17 by iel-amra          #+#    #+#             */
/*   Updated: 2023/07/01 16:12:37 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

using namespace std;

void Server::user(const Message &message)
{
	string answer;
	string param = message.getParameters();
	string username = word(param, 0, true);
	if ((message.getUser().getLevel() & 1) == 0)
		answer = string(ERR_PASSWDMISMATCH) + " :Password incorrect"; 
	else if (message.getUser().getLevel() & 8)
		answer = ERR_ALREADYREGISTERED;
	else
	{
		message.getUser().setUsername(username);
		message.getUser().setLevel(2);
		checkAuth(message.getUser());
	}
	respond(message.getUser().getNickname(), answer, message.getFd());
	return ;
}