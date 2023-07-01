#ifndef MESSAGE_HPP
# define MESSAGE_HPP
# include <iostream>
# include "./User.hpp" 
# include "./Channel.hpp"
# include <list>

// Format :    [{:}{prefix} {SP} ]{COMMANDE}[{SP}{PARAMETRES}]{CRLF}
/*
TO DO :
Client Message:
	CAP Message (optionnal)
	AUTHENTICATE Message (optionnal)
	PASS Message
	NICK Message
	USER Message 
	OPER Message(optionnal)
	QUIT Message(optionnal)
	ERROR Message(optionnal)
Channel Message:
	JOIN Message
	PART Message
	TOPIC Message
	NAMES Message
	LIST Message
	INVITE Message
		Invite list
	KICK Message
Sending Messages:
	PRIVMSG Messages
	NOTICE Message
*/

class Message {
	public:
	//canonical
		//Message(std::string name);
		Message(std::string name, User *user);
		Message(std::string name, User &user);
		Message( Message const &src);
		Message &	operator=( Message const &rhs);
		~Message(void);

	// getters
		std::string				getMessage( void ) const;
		std::string				getPrefix( void ) const;
		std::string				getCommand( void ) const;
		std::string				getParameters( void ) const;
		User					&getUser( void ) const;
		int						getFd( void ) const;
		std::string				getTags(void) const;

	// setters
		void	setMessage(std::string message);
		void	setPrefix(std::string prefix);
		void	setCommand(std::string command);
		void	setParameters(std::string parameters);
		void	setUser(User *user);
		void	setTags(std::string tags);

	// specific functions
		void	parseMessage( void );
		void	parseTag(std::string src, size_t begin);
		void	parseCommand(std::string src, size_t begin);
		void	parsePrefix(std::string src, size_t begin);

	protected:
	private:
		std::string	_message;
		std::string	_prefix;
		std::string	_tags;
		std::string	_command;
		std::string	_parameters;

		User		*_user;
};

std::ostream & operator << (std::ostream & o, Message const & i);

#endif
